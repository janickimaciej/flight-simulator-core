#include "physics/simulationBuffer.hpp"

#include "physics/simulationBufferPlayer.hpp"

#include <mutex>
#include <utility>

namespace Physics
{
	SimulationBuffer::SimulationBuffer(int ownId, Common::MapName map) :
		m_ownId{ownId}
	{
		for (std::unique_ptr<SimulationBufferElement>& bufferElement : m_buffer)
		{
			bufferElement = std::make_unique<SimulationBufferElement>(map);
		}
	}

	void SimulationBuffer::writeInitFrame(const SimulationStep& simulationStep, int playerId,
		const PlayerInfo& playerInfo)
	{
		std::scoped_lock lock{m_buffer[simulationStep.getStep()]->mutex};

		bool isSecondOdd = simulationStep.getSecond() % 2;
		if (!m_buffer[simulationStep.getStep()]->players.contains(playerId))
		{
			m_buffer[simulationStep.getStep()]->players.insert({playerId,
				SimulationBufferPlayer
				{
					std::array<bool, 2>
					{
						!isSecondOdd,
						isSecondOdd
					},
					std::array<bool, 2>
					{
						false,
						false
					},
					playerInfo
				}});
		}
	}

	void SimulationBuffer::writeControlFrame(const SimulationStep& simulationStep, int playerId,
		const PlayerInput& playerInput)
	{
		std::scoped_lock lock{m_buffer[simulationStep.getStep()]->mutex};

		bool isSecondOdd = simulationStep.getSecond() % 2;
		if (m_buffer[simulationStep.getStep()]->players.contains(playerId) &&
			!m_buffer[simulationStep.getStep()]->lock &&
			((!isSecondOdd &&
				!m_buffer[simulationStep.getStep()]->players.at(playerId).lockInput[0]) ||
			(isSecondOdd &&
				!m_buffer[simulationStep.getStep()]->players.at(playerId).lockInput[1])))
		{
			m_buffer[simulationStep.getStep()]->players.at(playerId).info.input = playerInput;
			m_buffer[simulationStep.getStep()]->players.at(playerId).lockInput[isSecondOdd] = true;
		}
	}

	void SimulationBuffer::writeStateFrame(const SimulationStep& simulationStep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		std::scoped_lock lock{m_buffer[simulationStep.getStep()]->mutex};

		addAndUpdatePlayers(simulationStep, playerInfos);
		removePlayers(simulationStep, playerInfos);
		m_buffer[simulationStep.getStep()]->lock = true;
	}

	void SimulationBuffer::writeOwnInput(const SimulationStep& simulationStep,
		const PlayerInput& ownInput)
	{
		writeControlFrame(simulationStep, m_ownId, ownInput);
	}

	void SimulationBuffer::kickPlayers(const std::vector<int>& kickedPlayers,
		const Physics::SimulationStep& simulationStep)
	{
		std::scoped_lock lock{m_buffer[simulationStep.getStep()]->mutex};

		bool isSecondOdd = simulationStep.getSecond() % 2;
		m_buffer[simulationStep.getStep()]->removedPlayers[isSecondOdd] = kickedPlayers;
	}

	void SimulationBuffer::update(const SimulationStep& simulationStep)
	{
		SimulationStep prevSimulationStep = simulationStep.prev();

		std::unordered_map<int, PlayerInfo> playerInfos{};
		std::unordered_map<int, bool> stateLocks{};
		{
			std::scoped_lock lock
			{
				m_buffer[prevSimulationStep.getStep()]->mutex,
				m_buffer[simulationStep.getStep()]->mutex
			};

			if (!m_buffer[simulationStep.getStep()]->lock)
			{
				addAndUpdatePlayers(prevSimulationStep, simulationStep);
				removePlayers(prevSimulationStep, simulationStep);
			}

			bool isSecondOdd = simulationStep.getSecond() % 2;
			for (const std::pair<const int, SimulationBufferPlayer>& player :
				m_buffer[simulationStep.getStep()]->players)
			{
				playerInfos.insert({player.first, player.second.info});
				stateLocks.insert({player.first,
					m_buffer[simulationStep.getStep()]->lock ||
					m_buffer[simulationStep.getStep()]->players[player.first].
						lockState[isSecondOdd]});
			}

			clearLocks(simulationStep);
		}

		m_buffer[simulationStep.getStep()]->scene.update(simulationStep,
			m_buffer[prevSimulationStep.getStep()]->scene, playerInfos, stateLocks);
	}

	Common::SceneInfo SimulationBuffer::getSceneInfo(const SimulationStep& simulationStep) const
	{
		return m_buffer[simulationStep.getStep()]->scene.getSceneInfo();
	}

	std::unordered_map<int, Physics::PlayerInfo> SimulationBuffer::getPlayerInfos(
		const SimulationStep& simulationStep) const
	{
		return m_buffer[simulationStep.getStep()]->scene.getPlayerInfos();
	}

	void SimulationBuffer::addAndUpdatePlayers(const SimulationStep& simulationStep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		for (const std::pair<const int, PlayerInfo>& playerInfo : playerInfos)
		{
			if (!m_buffer[simulationStep.getStep()]->players.contains(playerInfo.first))
			{
				m_buffer[simulationStep.getStep()]->players.insert({playerInfo.first,
					SimulationBufferPlayer
					{
						std::array<bool, 2>{},
						std::array<bool, 2>{},
						playerInfo.second
					}});
			}
			else
			{
				m_buffer[simulationStep.getStep()]->players[playerInfo.first].info =
					playerInfo.second;
			}
		}
	}

	void SimulationBuffer::removePlayers(const SimulationStep& simulationStep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[simulationStep.getStep()]->players)
		{
			if (!playerInfos.contains(player.first))
			{
				keysToBeDeleted.push_back(player.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[simulationStep.getStep()]->players.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdatePlayers(const SimulationStep& prevSimulationStep,
		const SimulationStep& simulationStep)
	{
		bool isSecondOdd = simulationStep.getSecond() % 2;
		for (const std::pair<const int, SimulationBufferPlayer>& prevSimulationStepPlayer :
			m_buffer[prevSimulationStep.getStep()]->players)
		{
			if (!m_buffer[simulationStep.getStep()]->players.
				contains(prevSimulationStepPlayer.first))
			{
				m_buffer[simulationStep.getStep()]->players.insert({prevSimulationStepPlayer.first,
					SimulationBufferPlayer
					{
						std::array<bool, 2>
						{
							false,
							false
						},
						std::array<bool, 2>
						{
							false,
							false
						},
						prevSimulationStepPlayer.second.info
					}});
			}
			else if (!m_buffer[simulationStep.getStep()]->players[prevSimulationStepPlayer.first].
				lockState[isSecondOdd] &&
				!m_buffer[simulationStep.getStep()]->players[prevSimulationStepPlayer.first].
				lockInput[isSecondOdd])
			{
				m_buffer[simulationStep.getStep()]->players[prevSimulationStepPlayer.first].
					info.input = prevSimulationStepPlayer.second.info.input;
			}
		}
	}

	void SimulationBuffer::removePlayers(const SimulationStep& prevSimulationStep,
		const SimulationStep& simulationStep)
	{
		bool isSecondOdd = simulationStep.getSecond() % 2;

		for (int player : m_buffer[simulationStep.getStep()]->removedPlayers[isSecondOdd])
		{
			m_buffer[simulationStep.getStep()]->players.erase(player);
		}

		std::vector<int> keysToBeDeleted;
		for (std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[simulationStep.getStep()]->players)
		{
			if (!player.second.lockState[isSecondOdd] &&
				!m_buffer[prevSimulationStep.getStep()]->players.contains(player.first))
			{
				keysToBeDeleted.push_back(player.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[simulationStep.getStep()]->players.erase(key);
		}
	}

	void SimulationBuffer::clearLocks(const SimulationStep& simulationStep)
	{
		m_buffer[simulationStep.getStep()]->lock = false;

		bool isSecondOdd = simulationStep.getSecond() % 2;
		m_buffer[simulationStep.getStep()]->removedPlayers[!isSecondOdd].clear();
		for (std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[simulationStep.getStep()]->players)
		{
			player.second.lockState[!isSecondOdd] = false;
			player.second.lockInput[!isSecondOdd] = false;
		}
	}
}
