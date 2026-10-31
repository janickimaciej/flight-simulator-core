#pragma once

#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
#include "physics/simulationBufferElement.hpp"
#include "physics/simulationStep.hpp"

#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Physics
{
	class SimulationBuffer
	{
	public:
		static constexpr int simulationBufferSize = SimulationStep::stepsPerSecond;

		SimulationBuffer(int ownId, Common::MapName map);

		void writeInitFrame(const SimulationStep& simulationStep, int playerId,
			const PlayerInfo& playerInfo);
		void writeControlFrame(const SimulationStep& simulationStep, int playerId,
			const PlayerInput& playerInput);
		void writeStateFrame(const SimulationStep& simulationStep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void writeOwnInput(const SimulationStep& simulationStep, const PlayerInput& ownInput);
		void kickPlayers(const std::vector<int>& kickedPlayers,
			const Physics::SimulationStep& simulationStep);
		void update(const SimulationStep& simulationStep);
		Common::SceneInfo getSceneInfo(const SimulationStep& simulationStep) const;
		std::unordered_map<int, Physics::PlayerInfo> getPlayerInfos(
			const SimulationStep& simulationStep) const;

	private:
		std::array<std::unique_ptr<SimulationBufferElement>, simulationBufferSize> m_buffer{};
		int m_ownId{};

		void addAndUpdatePlayers(const SimulationStep& simulationStep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void removePlayers(const SimulationStep& simulationStep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);

		void addAndUpdatePlayers(const SimulationStep& prevSimulationStep,
			const SimulationStep& simulationStep);
		void removePlayers(const SimulationStep& prevSimulationStep,
			const SimulationStep& simulationStep);

		void clearLocks(const SimulationStep& simulationStep);
	};
}
