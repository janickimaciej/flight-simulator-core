#include "physics/models/airplane.hpp"

#include "physics/airplaneDefinitions.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/flightCtrl.hpp"
#include "physics/modelDynamics/airplaneDynamics.hpp"
#include "physics/models/model.hpp"
#include "physics/playerInput.hpp"
#include "physics/timestep.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>

namespace Physics
{
	Airplane::Airplane(const Common::AirplaneTypeName& airplaneTypeName, int hp) :
		m_airplaneTypeName{airplaneTypeName},
		m_airplaneParams{airplaneDefinitions[Common::toSizeT(airplaneTypeName)].params},
		m_flightCtrl{m_airplaneParams, m_hp},
		m_dynamics{m_airplaneParams, m_flightCtrl},
		m_collisionModel{airplaneDefinitions[Common::toSizeT(airplaneTypeName)].collisionModel},
		m_hp{hp}
	{ }

	Airplane::Airplane(const Airplane& airplane) :
		m_airplaneTypeName{airplane.m_airplaneTypeName},
		m_airplaneParams{airplane.m_airplaneParams},
		m_flightCtrl{m_airplaneParams, m_hp},
		m_dynamics{m_airplaneParams, m_flightCtrl},
		m_collisionModel{airplane.m_collisionModel},
		m_lastShotTimestep{airplane.m_lastShotTimestep},
		m_hp{airplane.m_hp}
	{ }

	Airplane::Airplane(Airplane&& airplane) noexcept :
		m_airplaneTypeName{airplane.m_airplaneTypeName},
		m_airplaneParams{airplane.m_airplaneParams},
		m_flightCtrl{m_airplaneParams, m_hp},
		m_dynamics{m_airplaneParams, m_flightCtrl},
		m_collisionModel{airplane.m_collisionModel},
		m_lastShotTimestep{airplane.m_lastShotTimestep},
		m_hp{airplane.m_hp}
	{ }

	void Airplane::updatePhase1(const Airplane* previousAirplane, const PlayerInfo& playerInfo,
		bool isStateLocked)
	{
		m_flightCtrl.setPlayerInput(playerInfo.input);
		if (isStateLocked)
		{
			m_hp = playerInfo.state.hp;
		}
		else if (previousAirplane)
		{
			m_hp = previousAirplane->m_hp;
		}
		if (previousAirplane)
		{
			m_flightCtrl.update(previousAirplane->m_flightCtrl);
			setLastShotTimestep(previousAirplane->getLastShotTimestep());
		}
		if (isStateLocked)
		{
			setState(playerInfo.state.state);
		}
		else if (previousAirplane)
		{
			setState(previousAirplane->getState());
		}
	}

	void Airplane::updatePhase2()
	{
		setState(m_dynamics.computeNewState(getState()));
	}

	PlayerInfo Airplane::getPlayerInfo() const
	{
		return PlayerInfo
		{
			m_flightCtrl.getPlayerInput(),
			PlayerState
			{
				getAirplaneTypeName(),
				m_hp,
				getState()
			}
		};
	}

	Common::AirplaneInfo Airplane::getAirplaneInfo() const
	{
		return Common::AirplaneInfo
		{
			getState(),
			m_flightCtrl.getCtrl(),
			getAirplaneTypeName(),
			m_hp
		};
	}

	Common::AirplaneTypeName Airplane::getAirplaneTypeName() const
	{
		return m_airplaneTypeName;
	}

	const Common::AirplaneCtrl& Airplane::getCtrl() const
	{
		return m_flightCtrl.getCtrl();
	}

	const Collisions::Airplane& Airplane::getCollisionModel() const
	{
		return m_collisionModel;
	}

	const std::optional<Timestep>& Airplane::getLastShotTimestep() const
	{
		return m_lastShotTimestep;
	}

	void Airplane::setLastShotTimestep(const std::optional<Timestep>& lastShotTimestep)
	{
		m_lastShotTimestep = lastShotTimestep;
	}

	void Airplane::damage(int hp)
	{
		m_hp -= hp;
		if (m_hp < 0)
		{
			m_hp = 0;
		}
	}

	void Airplane::destroy()
	{
		m_hp = 0;
	}

	void Airplane::heal(int hp)
	{
		m_hp += hp;
		if (m_hp > 100)
		{
			m_hp = 100;
		}
	}
}
