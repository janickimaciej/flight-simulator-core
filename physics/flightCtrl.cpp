#include "physics/flightCtrl.hpp"

#include "common/airplaneCtrl.hpp"
#include "common/config.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/airplaneParams/surfaceParams.hpp"
#include "physics/playerInput.hpp"

#include <algorithm>

namespace Physics
{
	FlightCtrl::FlightCtrl(const AirplaneParams& airplaneParams, const int& hp) :
		m_airplaneParams{airplaneParams},
		m_hp{hp}
	{ }

	void FlightCtrl::update(const FlightCtrl& prevAirplaneFlightCtrl)
	{
		if (m_hp != 0)
		{
			updateElevator(prevAirplaneFlightCtrl.m_airplaneCtrl.elevatorAngleRad);
			updateRudder(prevAirplaneFlightCtrl.m_airplaneCtrl.rudderAngleRad);
			updateAilerons(prevAirplaneFlightCtrl.m_airplaneCtrl.aileronsAngleRad);
			updateThrust(prevAirplaneFlightCtrl.m_airplaneCtrl.thrustRelative);
			updateGunfire();
		}
		else
		{
			m_airplaneCtrl = Common::AirplaneCtrl{};
		}
	}

	float FlightCtrl::getElevatorAngleRad() const
	{
		return m_airplaneCtrl.elevatorAngleRad;
	}

	float FlightCtrl::getRudderAngleRad() const
	{
		return m_airplaneCtrl.rudderAngleRad;
	}

	float FlightCtrl::getAileronsAngleRad() const
	{
		return m_airplaneCtrl.aileronsAngleRad;
	}

	float FlightCtrl::getThrustRelative() const
	{
		return m_airplaneCtrl.thrustRelative;
	}

	const Common::AirplaneCtrl& FlightCtrl::getCtrl() const
	{
		return m_airplaneCtrl;
	}

	PlayerInput FlightCtrl::getPlayerInput() const
	{
		return m_playerInput;
	}

	void FlightCtrl::setPlayerInput(const PlayerInput& playerInput)
	{
		m_playerInput = playerInput;
	}

	void FlightCtrl::updateElevator(float prevElevatorAngleRad)
	{
		static constexpr float angVelocityRad = glm::radians(120.0f);
		static constexpr float maxChange = angVelocityRad / Common::stepsPerSecond;
		float diff = relativeToAbs(m_playerInput.pitch,
			m_airplaneParams.hStab.criticalAngleNegativeRad,
			m_airplaneParams.hStab.criticalAnglePositiveRad) - prevElevatorAngleRad;
		float change = std::clamp(diff, -maxChange, maxChange);
		m_airplaneCtrl.elevatorAngleRad = prevElevatorAngleRad + change;
	}

	void FlightCtrl::updateRudder(float prevRudderAngleRad)
	{
		static constexpr float angVelocityRad = glm::radians(120.0f);
		static constexpr float maxChange = angVelocityRad / Common::stepsPerSecond;
		float diff = relativeToAbs(m_playerInput.yaw,
			m_airplaneParams.hStab.criticalAngleNegativeRad,
			m_airplaneParams.hStab.criticalAnglePositiveRad) - prevRudderAngleRad;
		float change = std::clamp(diff, -maxChange, maxChange);
		m_airplaneCtrl.rudderAngleRad = prevRudderAngleRad + change;
	}

	void FlightCtrl::updateAilerons(float prevAileronsAngleRad)
	{
		static constexpr float angVelocityRad = glm::radians(120.0f);
		static constexpr float maxChange = angVelocityRad / Common::stepsPerSecond;
		float diff = relativeToAbs(m_playerInput.roll,
			m_airplaneParams.hStab.criticalAngleNegativeRad,
			m_airplaneParams.hStab.criticalAnglePositiveRad) - prevAileronsAngleRad;
		float change = std::clamp(diff, -maxChange, maxChange);
		m_airplaneCtrl.aileronsAngleRad = prevAileronsAngleRad + change;
	}

	void FlightCtrl::updateThrust(float prevThrustRelative)
	{
		static constexpr float velocity = 1;
		static constexpr float maxChange = velocity / Common::stepsPerSecond;
		float diff = m_playerInput.thrust - prevThrustRelative;
		float change = std::clamp(diff, -maxChange, maxChange);
		m_airplaneCtrl.thrustRelative = prevThrustRelative + change;
	}

	void FlightCtrl::updateGunfire()
	{
		m_airplaneCtrl.gunfire = m_playerInput.trigger;
	}

	float FlightCtrl::relativeToAbs(float relative, float min, float max)
	{
		return (min + max + relative * (max - min)) / 2;
	}
}
