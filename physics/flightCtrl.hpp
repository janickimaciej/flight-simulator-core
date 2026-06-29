#pragma once

#include "common/airplaneCtrl.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/playerInput.hpp"

namespace Physics
{
	class FlightCtrl
	{
	public:
		FlightCtrl(const AirplaneParams& airplaneParams, const int& hp);
		void update(const FlightCtrl& previousAirplaneFlightCtrl);
		float getElevatorAngleRad() const;
		float getRudderAngleRad() const;
		float getAileronsAngleRad() const;
		float getThrustRelative() const;
		PlayerInput getPlayerInput() const;
		void setPlayerInput(const PlayerInput& playerInput);
		const Common::AirplaneCtrl& getCtrl() const;

	private:
		const AirplaneParams& m_airplaneParams;
		PlayerInput m_playerInput{};
		Common::AirplaneCtrl m_airplaneCtrl{};
		const int& m_hp;

		void updateElevator(float previousElevatorAngleRad);
		void updateRudder(float previousRudderAngleRad);
		void updateAilerons(float previousAileronsAngleRad);
		void updateThrust(float previousThrustRelative);
		void updateGunfire();
		// converts linearly from [-1, 1] to [min, max]
		static float relativeToAbs(float relative, float min, float max);
	};
}
