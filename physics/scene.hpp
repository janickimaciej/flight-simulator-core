#pragma once

#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "common/terrains/maps/map.hpp"
#include "physics/dayNightCycle.hpp"
#include "physics/models/airplane.hpp"
#include "physics/models/bullet.hpp"
#include "physics/playerInfo.hpp"
#include "physics/timestep.hpp"

#include <list>
#include <unordered_map>

namespace Physics
{
	class Scene
	{
	public:
		Scene(Common::MapName mapName);
		void update(const Timestep& timestep, const Scene& previousScene,
			const std::unordered_map<int, PlayerInfo>& playerInfos,
			const std::unordered_map<int, bool>& stateLocks);
		Common::SceneInfo getSceneInfo() const;
		std::unordered_map<int, PlayerInfo> getPlayerInfos() const;

	private:
		std::unordered_map<int, Airplane> m_airplanes{};
		std::unordered_map<int, std::list<Bullet>> m_bullets{};

		DayNightCycle m_dayNightCycle{};

		const Common::Terrains::Map& m_map;
		
		void addAndUpdateAirplanes(const Scene& previousScene,
			const std::unordered_map<int, PlayerInfo>& playerInfos,
			const std::unordered_map<int, bool>& stateLocks, const Timestep& timestep);
		void removeAirplanes(const Scene& previousScene,
			const std::unordered_map<int, bool>& stateLocks);
		void updateBullets(const Timestep& timestep, const Scene& previousScene);
		void updateAirplanePhase1(int index, const Scene& previousScene,
			const PlayerInfo& playerInfo, bool isStateLocked);
		void updateAirplanePhase2(int index, const Timestep& timestep);
		bool updateBullet(Bullet& bullet);
	};
}
