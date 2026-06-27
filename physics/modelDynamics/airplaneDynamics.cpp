#include "physics/modelDynamics/airplaneDynamics.hpp"

#include "common/state.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/airplaneParams/fuselageParams.hpp"
#include "physics/airplaneParams/inertiaParams.hpp"
#include "physics/airplaneParams/propulsionParams.hpp"
#include "physics/airplaneParams/surfaceParams.hpp"
#include "physics/atmosphere.hpp"
#include "physics/flightCtrl.hpp"
#include "physics/modelDynamics/rigidBodyDynamics.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	static constexpr float eps = 1e-9f;

	AirplaneDynamics::AirplaneDynamics(const AirplaneParams& params,
		const FlightCtrl& flightCtrl) :
		RigidBodyDynamics{params.inertia.mass, params.inertia.momentOfInertia},
		m_params{params},
		m_flightCtrl{flightCtrl}
	{ }

	void AirplaneDynamics::computeNetForceAndNetTorque(const Common::State& state,
		glm::vec3& netForce, glm::vec3& netTorque) const
	{
		netForce = glm::vec3{0, 0, 0};
		netTorque = glm::vec3{0, 0, 0};

		addForceAndTorque(state, m_params.inertia, netForce, netTorque);
		addForceAndTorque(state, m_params.hStab, m_flightCtrl.getElevatorAngleRad(), netForce,
			netTorque);
		addForceAndTorque(state, m_params.vStab, m_flightCtrl.getRudderAngleRad(), netForce,
			netTorque);
		addForceAndTorque(state, m_params.leftWing, -m_flightCtrl.getAileronsAngleRad(), netForce,
			netTorque);
		addForceAndTorque(state, m_params.rightWing, m_flightCtrl.getAileronsAngleRad(), netForce,
			netTorque);
		addForceAndTorque(state, m_params.fuselage, netForce, netTorque);
		addForceAndTorque(state, m_params.propulsion, m_flightCtrl.getThrustRelative(), netForce,
			netTorque);
	}

	void AirplaneDynamics::addForceAndTorque(const Common::State& state,
		const InertiaParams& params, glm::vec3& netForce, glm::vec3&)
	{
		static constexpr float g = 9.81f;

		glm::vec3 gravityDirectionGlobal{0, -1, 0};
		glm::vec3 gravityGlobal = params.mass * g * gravityDirectionGlobal;
		glm::vec3 gravity = glm::conjugate(state.orientation) * gravityGlobal;
		netForce += gravity;
	}

	void AirplaneDynamics::addForceAndTorque(const Common::State& state,
		const SurfaceParams& params, float ctrlAngleRad, glm::vec3& netForce, glm::vec3& netTorque)
	{
		float airDensity = Atmosphere::airDensity(state.position.y);

		glm::vec3 airVelocity = computeAirVelocity(state, params.liftPoint);
		glm::vec3 airVelocitySurface = glm::conjugate(params.orientation) * airVelocity;
		glm::vec3 yzAirVelocitySurface = glm::vec3{0, airVelocitySurface.y, airVelocitySurface.z};
		float yzAirSpeed = glm::length(yzAirVelocitySurface);
		float angleOfAttackSurfaceRad = glm::atan(yzAirVelocitySurface.y, yzAirVelocitySurface.z);
		if (yzAirSpeed > eps && angleOfAttackSurfaceRad > params.criticalAngleNegativeRad &&
			angleOfAttackSurfaceRad < params.criticalAnglePositiveRad)
		{
			float dynamicPressure = airDensity * yzAirSpeed * yzAirSpeed / 2;
			float liftCoef = params.liftCoefConst + params.liftCoefDeriv * angleOfAttackSurfaceRad;
			glm::vec3 liftDirectionSurface = glm::normalize(glm::cross(yzAirVelocitySurface,
				glm::vec3{1, 0, 0}));
			glm::vec3 liftSurface = dynamicPressure * params.area * liftCoef * liftDirectionSurface;
			glm::vec3 lift = params.orientation * liftSurface;
			netForce += lift;
			netTorque += glm::cross(params.liftPoint, lift);
		}

		airVelocity = computeAirVelocity(state, params.ctrlLiftPoint);
		airVelocitySurface = glm::conjugate(params.orientation) * airVelocity;
		yzAirVelocitySurface = glm::vec3{0, airVelocitySurface.y, airVelocitySurface.z};
		yzAirSpeed = glm::length(yzAirVelocitySurface);
		angleOfAttackSurfaceRad = glm::atan(yzAirVelocitySurface.y, yzAirVelocitySurface.z);
		if (yzAirSpeed > eps && angleOfAttackSurfaceRad > params.criticalAngleNegativeRad &&
			angleOfAttackSurfaceRad < params.criticalAnglePositiveRad)
		{
			float dynamicPressure = airDensity * yzAirSpeed * yzAirSpeed / 2;
			float ctrlLiftCoef = -params.ctrlLiftCoefDeriv * ctrlAngleRad;
			glm::vec3 ctrlLiftDirectionSurface = glm::normalize(glm::cross(yzAirVelocitySurface,
				glm::vec3{1, 0, 0}));
			glm::vec3 ctrlLiftSurface = dynamicPressure * params.ctrlArea * ctrlLiftCoef *
				ctrlLiftDirectionSurface;
			glm::vec3 ctrlLift = params.orientation * ctrlLiftSurface;
			netForce += ctrlLift;
			netTorque += glm::cross(params.ctrlLiftPoint, ctrlLift);
		}

		airVelocity = computeAirVelocity(state, params.normalForcePoint);
		airVelocitySurface = glm::conjugate(params.orientation) * airVelocity;
		if (glm::abs(airVelocitySurface.y) > eps)
		{
			float dynamicPressure = airDensity * airVelocitySurface.y * airVelocitySurface.y / 2;
			glm::vec3 normalForceDirectionSurface =
				glm::vec3{0, airVelocitySurface.y > 0 ? 1 : -1, 0};
			glm::vec3 normalForceSurface = dynamicPressure * params.area * params.normalForceCoef *
				normalForceDirectionSurface;
			glm::vec3 normalForce = params.orientation * normalForceSurface;
			netForce += normalForce;
			netTorque += glm::cross(params.normalForcePoint, normalForce);
		}
	}

	void AirplaneDynamics::addForceAndTorque(const Common::State& state,
		const FuselageParams& params, glm::vec3& netForce, glm::vec3& netTorque)
	{
		float airDensity = Atmosphere::airDensity(state.position.y);

		glm::vec3 airVelocity = computeAirVelocity(state, params.frontDragPoint);
		if (glm::abs(airVelocity.z) > eps)
		{
			float dynamicPressure = airDensity * airVelocity.z * airVelocity.z / 2;
			glm::vec3 frontDragDirection = glm::vec3{0, 0, airVelocity.z > 0 ? 1 : -1};
			glm::vec3 frontDrag = dynamicPressure * params.frontArea * params.frontDragCoef *
				frontDragDirection;
			netForce += frontDrag;
			netTorque += glm::cross(params.frontDragPoint, frontDrag);
		}

		airVelocity = computeAirVelocity(state, params.sideDragPoint);
		glm::vec3 xyAirVelocity = glm::vec3{airVelocity.x, airVelocity.y, 0};
		float xyAirSpeed = glm::length(xyAirVelocity);
		if (xyAirSpeed > eps)
		{
			float dynamicPressure = airDensity * xyAirSpeed * xyAirSpeed / 2;
			glm::vec3 sideDragDirection = xyAirVelocity / xyAirSpeed;
			glm::vec3 sideDrag = dynamicPressure * params.sideArea * params.sideDragCoef *
				sideDragDirection;
			netForce += sideDrag;
			netTorque += glm::cross(params.sideDragPoint, sideDrag);
		}
	}

	void AirplaneDynamics::addForceAndTorque(const Common::State& state,
		const PropulsionParams& params, float thrustRelative, glm::vec3& netForce,
		glm::vec3& netTorque)
	{
		float airDensityRelative = Atmosphere::airDensity(state.position.y) /
			Atmosphere::seaLevelAirDensity;

		glm::vec3 thrustDirection = glm::vec3{0, 0, -1};
		glm::vec3 thrust = thrustRelative * airDensityRelative * params.maxThrust * thrustDirection;
		netForce += thrust;
		netTorque += glm::cross(params.thrustPoint, thrust);
	}

	glm::vec3 AirplaneDynamics::computeAirVelocity(const Common::State& state,
		const glm::vec3& point)
	{
		return -state.velocity - glm::cross(state.angVelocityRad, point);
	}
}
