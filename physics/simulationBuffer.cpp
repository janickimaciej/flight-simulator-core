#include "physics/simulationBuffer.hpp"

#include "common/airplaneInfo.hpp"
#include "common/mapName.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
#include "physics/playerState.hpp"
#include "physics/simulationBufferElement.hpp"
#include "physics/simulationBufferPlayer.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <vector>

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

	void SimulationBuffer::writeInitFrame(const Timestep& timestep, int playerId,
		const PlayerInfo& playerInfo)
	{
		m_buffer[timestep.step]->mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		if (!m_buffer[timestep.step]->players.contains(playerId))
		{
			m_buffer[timestep.step]->players.insert({playerId,
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

		m_buffer[timestep.step]->mutex.unlock();
	}

	void SimulationBuffer::writeControlFrame(const Timestep& timestep, int playerId,
		const PlayerInput& playerInput)
	{
		m_buffer[timestep.step]->mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		if (m_buffer[timestep.step]->players.contains(playerId) && !m_buffer[timestep.step]->lock &&
			((!isSecondOdd && !m_buffer[timestep.step]->players.at(playerId).lockInput[0]) ||
			(isSecondOdd && !m_buffer[timestep.step]->players.at(playerId).lockInput[1])))
		{
			m_buffer[timestep.step]->players.at(playerId).info.input = playerInput;
			m_buffer[timestep.step]->players.at(playerId).lockInput[isSecondOdd] = true;
		}

		m_buffer[timestep.step]->mutex.unlock();
	}

	void SimulationBuffer::writeStateFrame(const Timestep& timestep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		m_buffer[timestep.step]->mutex.lock();

		addAndUpdatePlayers(timestep, playerInfos);
		removePlayers(timestep, playerInfos);
		m_buffer[timestep.step]->lock = true;

		m_buffer[timestep.step]->mutex.unlock();
	}

	void SimulationBuffer::writeOwnInput(const Timestep& timestep, const PlayerInput& ownInput)
	{
		writeControlFrame(timestep, m_ownId, ownInput);
	}

	void SimulationBuffer::kickPlayers(const std::vector<int>& kickedPlayers,
		const Physics::Timestep& timestep)
	{
		m_buffer[timestep.step]->mutex.lock();

		bool isSecondOdd = timestep.second % 2;
		m_buffer[timestep.step]->removedPlayers[isSecondOdd] = kickedPlayers;

		m_buffer[timestep.step]->mutex.unlock();
	}

	void SimulationBuffer::update(const Timestep& timestep)
	{
		Timestep prevTimestep = timestep.prev();

		m_buffer[prevTimestep.step]->mutex.lock();
		m_buffer[timestep.step]->mutex.lock();

		if (!m_buffer[timestep.step]->lock)
		{
			addAndUpdatePlayers(prevTimestep, timestep);
			removePlayers(prevTimestep, timestep);
		}

		bool isSecondOdd = timestep.second % 2;
		std::unordered_map<int, PlayerInfo> playerInfos;
		std::unordered_map<int, bool> stateLocks;
		for (const std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.step]->players)
		{
			playerInfos.insert({player.first, player.second.info});
			stateLocks.insert({player.first,
				m_buffer[timestep.step]->lock ||
				m_buffer[timestep.step]->players[player.first].lockState[isSecondOdd]});
		}

		clearLocks(timestep);

		m_buffer[prevTimestep.step]->mutex.unlock();
		m_buffer[timestep.step]->mutex.unlock();

		m_buffer[timestep.step]->scene.update(timestep, m_buffer[prevTimestep.step]->scene,
			playerInfos, stateLocks);
	}

	Common::SceneInfo SimulationBuffer::getSceneInfo(const Timestep& timestep) const
	{
		return m_buffer[timestep.step]->scene.getSceneInfo();
	}

	std::unordered_map<int, Physics::PlayerInfo> SimulationBuffer::getPlayerInfos(
		const Timestep& timestep) const
	{
		return m_buffer[timestep.step]->scene.getPlayerInfos();
	}

	void SimulationBuffer::addAndUpdatePlayers(const Timestep& timestep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		for (const std::pair<const int, PlayerInfo>& playerInfo : playerInfos)
		{
			if (!m_buffer[timestep.step]->players.contains(playerInfo.first))
			{
				m_buffer[timestep.step]->players.insert({playerInfo.first,
					SimulationBufferPlayer
					{
						std::array<bool, 2>{},
						std::array<bool, 2>{},
						playerInfo.second
					}});
			}
			else
			{
				m_buffer[timestep.step]->players[playerInfo.first].info = playerInfo.second;
			}
		}
	}

	void SimulationBuffer::removePlayers(const Timestep& timestep,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.step]->players)
		{
			if (!playerInfos.contains(player.first))
			{
				keysToBeDeleted.push_back(player.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.step]->players.erase(key);
		}
	}

	void SimulationBuffer::addAndUpdatePlayers(const Timestep& prevTimestep,
		const Timestep& timestep)
	{
		bool isSecondOdd = timestep.second % 2;
		for (const std::pair<const int, SimulationBufferPlayer>& prevTimestepPlayer :
			m_buffer[prevTimestep.step]->players)
		{
			if (!m_buffer[timestep.step]->players.contains(prevTimestepPlayer.first))
			{
				m_buffer[timestep.step]->players.insert({prevTimestepPlayer.first,
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
						prevTimestepPlayer.second.info
					}});
			}
			else if (!m_buffer[timestep.step]->players[prevTimestepPlayer.first].
				lockState[isSecondOdd] &&
				!m_buffer[timestep.step]->players[prevTimestepPlayer.first].
				lockInput[isSecondOdd])
			{
				m_buffer[timestep.step]->players[prevTimestepPlayer.first].info.input =
					prevTimestepPlayer.second.info.input;
			}
		}
	}

	void SimulationBuffer::removePlayers(const Timestep& prevTimestep,
		const Timestep& timestep)
	{
		bool isSecondOdd = timestep.second % 2;

		for (int player : m_buffer[timestep.step]->removedPlayers[isSecondOdd])
		{
			m_buffer[timestep.step]->players.erase(player);
		}

		std::vector<int> keysToBeDeleted;
		for (std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.step]->players)
		{
			if (!player.second.lockState[isSecondOdd] &&
				!m_buffer[prevTimestep.step]->players.contains(player.first))
			{
				keysToBeDeleted.push_back(player.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_buffer[timestep.step]->players.erase(key);
		}
	}

	void SimulationBuffer::clearLocks(const Timestep& timestep)
	{
		m_buffer[timestep.step]->lock = false;

		bool isSecondOdd = timestep.second % 2;
		m_buffer[timestep.step]->removedPlayers[!isSecondOdd].clear();
		for (std::pair<const int, SimulationBufferPlayer>& player :
			m_buffer[timestep.step]->players)
		{
			player.second.lockState[!isSecondOdd] = false;
			player.second.lockInput[!isSecondOdd] = false;
		}
	}
}
