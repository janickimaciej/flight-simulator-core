#pragma once

#include "common/config.hpp"
#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
#include "physics/simulationBufferElement.hpp"
#include "physics/simulationBufferPlayer.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Physics
{
	class SimulationBuffer
	{
	public:
		static constexpr int simulationBufferSize = Common::stepsPerSecond;

		SimulationBuffer(int ownId, Common::MapName map);

		void writeInitFrame(const Timestep& timestep, int playerId, const PlayerInfo& playerInfo);
		void writeControlFrame(const Timestep& timestep, int playerId,
			const PlayerInput& playerInput);
		void writeStateFrame(const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void writeOwnInput(const Timestep& timestep, const PlayerInput& ownInput);
		void kickPlayers(const std::vector<int>& kickedPlayers, const Physics::Timestep& timestep);
		void update(const Timestep& timestep);
		Common::SceneInfo getSceneInfo(const Timestep& timestep) const;
		std::unordered_map<int, Physics::PlayerInfo> getPlayerInfos(const Timestep& timestep) const;

	private:
		std::array<std::unique_ptr<SimulationBufferElement>, simulationBufferSize> m_buffer{};
		int m_ownId{};

		void addAndUpdatePlayers(const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void removePlayers(const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);

		void addAndUpdatePlayers(const Timestep& previousTimestep, const Timestep& timestep);
		void removePlayers(const Timestep& previousTimestep, const Timestep& timestep);

		void clearLocks(const Timestep& timestep);
	};
}
