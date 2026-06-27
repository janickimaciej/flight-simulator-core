#pragma once

#include "physics/airplaneParams/fuselageParams.hpp"
#include "physics/airplaneParams/inertiaParams.hpp"
#include "physics/airplaneParams/propulsionParams.hpp"
#include "physics/airplaneParams/surfaceParams.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	struct AirplaneParams
	{
		InertiaParams inertia;
		SurfaceParams hStab;
		SurfaceParams vStab;
		SurfaceParams leftWing;
		SurfaceParams rightWing;
		FuselageParams fuselage;
		PropulsionParams propulsion;

		AirplaneParams
		(
			float mass, const glm::mat3& momentOfInertia, const glm::vec3& centerOfMass,

			float hStabIncidenceDeg, float hStabArea, float hStabLiftCoefConst,
			float hStabLiftCoefDeriv, float hStabNormalForceCoef,
			float hStabCriticalAngleNegativeDeg, float hStabCriticalAnglePositiveDeg,
			const glm::vec3& hStabLiftPoint, const glm::vec3& hStabNormalForcePoint,
			float elevatorArea, float elevatorLiftCoefDeriv, float elevatorMinAngleDeg,
			float elevatorMaxAngleDeg, const glm::vec3& elevatorForcePoint,

			float vStabIncidenceDeg, float vStabArea, float vStabLiftCoefConst,
			float vStabLiftCoefDeriv, float vStabNormalForceCoef,
			float vStabCriticalAngleNegativeDeg, float vStabCriticalAnglePositiveDeg,
			const glm::vec3& vStabLiftPoint, const glm::vec3& vStabNormalForcePoint,
			float rudderArea, float rudderLiftCoefDeriv, float rudderMaxAngleDeg,
			const glm::vec3& rudderForcePoint,

			float wingsIncidenceAngleDeg, float wingsArea, float wingsLiftCoefConst,
			float wingsLiftCoefDeriv, float wingsNormalForceCoef,
			float wingsCriticalAngleNegativeDeg, float wingsCriticalAnglePositiveDeg,
			const glm::vec3& rightWingLiftPoint, const glm::vec3& rightWingNormalForcePoint,
			float aileronsArea, float aileronsLiftCoefDeriv, float aileronsMaxAngleDeg,
			const glm::vec3& rightAileronForcePoint,

			float fuselageFrontArea, float fuselageFrontDragCoef,
			const glm::vec3& fuselageFrontDragPoint, float fuselageSideArea,
			float fuselageSideDragCoef, const glm::vec3& fuselageSideDragPoint,

			float maxThrust, const glm::vec3& thrustPoint
		);
		AirplaneParams(const AirplaneParams&) = default;

	private:
		static float adjustLiftCoefDeriv(float liftCoefDeriv, float criticalAngleNegativeRad,
			float criticalAnglePositiveRad);
	};
}
