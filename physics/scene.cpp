#include "scene.hpp"

#include "common/airplaneCentersOfMass.hpp"
#include "common/airplaneInfo.hpp"
#include "common/airplaneType.hpp"
#include "common/bulletInfo.hpp"
#include "common/config.hpp"
#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "common/terrains/maps/maps.hpp"
#include "physics/airplaneDefinitions.hpp"
#include "physics/collisions/collisionTest.hpp"
#include "physics/models/airplane.hpp"
#include "physics/playerInfo.hpp"
#include "physics/timestep.hpp"

#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Physics
{
	Scene::Scene(Common::MapName map) :
		m_map{*Common::Terrains::maps[Common::toSizeT(map)]}
	{ }

	void Scene::update(const Timestep& timestep, const Scene& prevScene,
		const std::unordered_map<int, PlayerInfo>& playerInfos,
		const std::unordered_map<int, bool>& stateLocks)
	{
		addAndUpdateAirplanes(prevScene, playerInfos, stateLocks, timestep);
		removeAirplanes(prevScene, stateLocks);
		updateBullets(timestep, prevScene);
		m_dayNightCycle.updateTime(prevScene.m_dayNightCycle);
	}

	Common::SceneInfo Scene::getSceneInfo() const
	{
		Common::SceneInfo sceneInfo{};
		for (const std::pair<const int, Airplane>& airplane : m_airplanes)
		{
			sceneInfo.airplaneInfos.insert({airplane.first, airplane.second.getAirplaneInfo()});
		}
		for (const std::pair<const int, std::list<Bullet>>& bullets : m_bullets)
		{
			for (const Bullet& bullet : bullets.second)
			{
				sceneInfo.bulletInfos.push_back(Common::BulletInfo{bullet.getState()});
			}
		}
		sceneInfo.day = m_dayNightCycle.getDay();
		sceneInfo.timeOfDay = m_dayNightCycle.getTimeOfDay();
		return sceneInfo;
	}

	std::unordered_map<int, PlayerInfo> Scene::getPlayerInfos() const
	{
		std::unordered_map<int, PlayerInfo> playerInfos{};
		for (const std::pair<const int, Airplane>& airplane : m_airplanes)
		{
			playerInfos.insert({airplane.first, airplane.second.getPlayerInfo()});
		}
		return playerInfos;
	}

	void Scene::addAndUpdateAirplanes(const Scene& prevScene,
		const std::unordered_map<int, PlayerInfo>& playerInfos,
		const std::unordered_map<int, bool>& stateLocks, const Timestep& timestep)
	{
		for (const std::pair<const int, bool>& stateLock : stateLocks)
		{
			int index = stateLock.first;

			if (!m_airplanes.contains(index))
			{
				Common::AirplaneType airplaneType =
					playerInfos.at(stateLock.first).state.airplaneType;
				m_airplanes.insert({index,
					Airplane
					{
						airplaneType,
						airplaneDefinitions[toSizeT(airplaneType)].initialHP
					}});
				m_bullets.insert({index, std::list<Bullet>{}});
			}

			updateAirplanePhase1(index, prevScene, playerInfos.at(index), stateLocks.at(index));
		}

		for (const std::pair<const int, bool>& stateLock : stateLocks)
		{
			if (!stateLock.second)
			{
				updateAirplanePhase2(stateLock.first, timestep);
			}
		}
	}

	void Scene::removeAirplanes(const Scene& prevScene,
		const std::unordered_map<int, bool>& stateLocks)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, Airplane>& airplane : m_airplanes)
		{
			if (!stateLocks.contains(airplane.first) ||
				(!stateLocks.at(airplane.first) &&
				!prevScene.m_airplanes.contains(airplane.first)))
			{
				keysToBeDeleted.push_back(airplane.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_airplanes.erase(key);
			m_bullets.erase(key);
		}
	}

	void Scene::updateBullets(const Timestep& timestep, const Scene& prevScene)
	{
		for (std::pair<const int, std::list<Bullet>>& bullets : m_bullets)
		{
			int id = bullets.first;
			if (prevScene.m_bullets.contains(id))
			{
				bullets.second = prevScene.m_bullets.at(id);
			}

			std::optional<Timestep> lastShotTimestep = m_airplanes.at(id).getLastShotTimestep();

			static constexpr Timestep bulletLifetime{5, 0};
			if (lastShotTimestep.has_value() && timestep - *lastShotTimestep > bulletLifetime)
			{
				m_airplanes.at(id).setLastShotTimestep(std::nullopt);
			}
			while (!bullets.second.empty() &&
				timestep - bullets.second.back().getSpawnTimestep() > bulletLifetime)
			{
				bullets.second.pop_back();
			}

			for (std::list<Bullet>::iterator iter = bullets.second.begin();
				iter != bullets.second.end();)
			{
				if (updateBullet(*iter))
				{
					iter = bullets.second.erase(iter);
				}
				else
				{
					++iter;
				}
			}

			static constexpr Timestep bulletCooldown{0, Common::stepsPerSecond / 10};
			if (m_airplanes.at(id).getCtrl().gunfire &&
				(!m_airplanes.at(id).getLastShotTimestep().has_value() ||
				timestep - *m_airplanes.at(id).getLastShotTimestep() > bulletCooldown))
			{
				Common::State airplaneState = m_airplanes.at(id).getState();
				Common::AirplaneType airplaneType =
					m_airplanes.at(id).getAirplaneType();
				glm::vec3 initialPosLocal = airplaneDefinitions[toSizeT(airplaneType)].muzzlePos +
					glm::vec3{0, 0, -Common::tracerLength};
				glm::vec3 initialVelocityLocal =
					airplaneDefinitions[toSizeT(airplaneType)].muzzleVelocity;

				Common::State state{};
				state.pos = glm::vec3{airplaneState.matrix() * glm::vec4{initialPosLocal, 1}};
				state.orientation = airplaneState.orientation;
				state.velocity = airplaneState.velocity + initialVelocityLocal;

				bullets.second.push_front(Bullet{state, timestep});
				m_airplanes.at(id).setLastShotTimestep(timestep);
			}
		}
	}

	void Scene::updateAirplanePhase1(int index, const Scene& prevScene,
		const PlayerInfo& playerInfo, bool isStateLocked)
	{
		const Airplane* prevAirplane = prevScene.m_airplanes.contains(index) ?
			&prevScene.m_airplanes.at(index) : nullptr;
		m_airplanes.at(index).updatePhase1(prevAirplane, playerInfo, isStateLocked);
	}

	void Scene::updateAirplanePhase2(int index, const Timestep& timestep)
	{
		Airplane& airplane = m_airplanes.at(index);
		Common::State prevState = airplane.getState();
		airplane.updatePhase2();
		Common::State nextState = airplane.getState();

		if (m_map.isOutside(airplane.getPos()))
		{
			if (timestep.step == 0)
			{
				static constexpr int outsideMapDamage = 5;
				airplane.damage(outsideMapDamage);
			}
		}
		else if (Collisions::CollisionTest::collides(airplane.getCollisionModel(), prevState,
			nextState, m_map))
		{
			airplane.destroy();
			return;
		}

		for (const std::pair<const int, Airplane>& otherAirplane : m_airplanes)
		{
			if (otherAirplane.first == index)
			{
				continue;
			}

			if (Collisions::CollisionTest::collides(airplane.getCollisionModel(), prevState,
				nextState, otherAirplane.second.getCollisionModel(),
				otherAirplane.second.getState()))
			{
				airplane.destroy();
				return;
			}
		}
	}

	bool Scene::updateBullet(Bullet& bullet)
	{
		Common::State prevState = bullet.getState();
		bullet.update(bullet);
		Common::State nextState = bullet.getState();
		if (Collisions::CollisionTest::collides(glm::vec3{0, 0, 0}, prevState, nextState,
			m_map))
		{
			return true;
		}
		for (std::pair<const int, Airplane>& airplane : m_airplanes)
		{
			if (Collisions::CollisionTest::collides(glm::vec3{0, 0, 0}, prevState, nextState,
				airplane.second.getCollisionModel(), airplane.second.getState()))
			{
				const int bulletDamage = 20;
				airplane.second.damage(bulletDamage);
				return true;
			}
		}
		return false;
	}
}
