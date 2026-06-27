#pragma once

#include "common/state.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/airplaneParams/fuselageParams.hpp"
#include "physics/airplaneParams/inertiaParams.hpp"
#include "physics/airplaneParams/propulsionParams.hpp"
#include "physics/airplaneParams/surfaceParams.hpp"
#include "physics/flightCtrl.hpp"
#include "physics/modelDynamics/rigidBodyDynamics.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	class AirplaneDynamics : public RigidBodyDynamics
	{
	public:
		AirplaneDynamics(const AirplaneParams& params, const FlightCtrl& flightCtrl);
		virtual ~AirplaneDynamics() = default;

	private:
		const AirplaneParams& m_params;
		const FlightCtrl& m_flightCtrl;

		virtual void computeNetForceAndNetTorque(const Common::State& state, glm::vec3& netForce,
			glm::vec3& netTorque) const override;

		static void addForceAndTorque(const Common::State& state, const InertiaParams& params,
			glm::vec3& netForce, glm::vec3&);
		static void addForceAndTorque(const Common::State& state, const SurfaceParams& params,
			float ctrlAngleRad, glm::vec3& netForce, glm::vec3& netTorque);
		static void addForceAndTorque(const Common::State& state, const FuselageParams& params,
			glm::vec3& netForce, glm::vec3& netTorque);
		static void addForceAndTorque(const Common::State& state, const PropulsionParams& params,
			float thrustRelative, glm::vec3& netForce, glm::vec3& netTorque);

		static glm::vec3 computeAirVelocity(const Common::State& state, const glm::vec3& point);
	};
}
