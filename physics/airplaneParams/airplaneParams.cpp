#include "physics/airplaneParams/airplaneParams.hpp"

#include "physics/airplaneParams/fuselageParams.hpp"
#include "physics/airplaneParams/inertiaParams.hpp"
#include "physics/airplaneParams/propulsionParams.hpp"
#include "physics/airplaneParams/surfaceParams.hpp"

#include <glm/glm.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Physics
{
	AirplaneParams::AirplaneParams
	(
		float mass, const glm::mat3& momentOfInertia, const glm::vec3& centerOfMass,

		float hStabIncidenceAngleDeg, float hStabArea, float hStabLiftCoefConst,
		float hStabLiftCoefDeriv, float hStabNormalForceCoef, float hStabCriticalAngleNegativeDeg,
		float hStabCriticalAnglePositiveDeg, const glm::vec3& hStabLiftPoint,
		const glm::vec3& hStabNormalForcePoint, float elevatorArea, float elevatorLiftCoefDeriv,
		float elevatorMinAngleDeg, float elevatorMaxAngleDeg, const glm::vec3& elevatorForcePoint,

		float vStabIncidenceAngleDeg, float vStabArea, float vStabLiftCoefConst,
		float vStabLiftCoefDeriv, float vStabNormalForceCoef, float vStabCriticalAngleNegativeDeg,
		float vStabCriticalAnglePositiveDeg, const glm::vec3& vStabLiftPoint,
		const glm::vec3& vStabNormalForcePoint, float rudderArea, float rudderLiftCoefDeriv,
		float rudderMaxAngleDeg, const glm::vec3& rudderForcePoint,

		float wingsIncidenceAngleDeg, float wingsArea, float wingsLiftCoefConst,
		float wingsLiftCoefDeriv, float wingsNormalForceCoef, float wingsCriticalAngleNegativeDeg,
		float wingsCriticalAnglePositiveDeg, const glm::vec3& rightWingLiftPoint,
		const glm::vec3& rightWingNormalForcePoint, float aileronsArea, float aileronsLiftCoefDeriv,
		float aileronsMaxAngleDeg, const glm::vec3& rightAileronForcePoint,

		float fuselageFrontArea, float fuselageFrontDragCoef,
		const glm::vec3& fuselageFrontDragPoint, float fuselageSideArea, float fuselageSideDragCoef,
		const glm::vec3& fuselageSideDragPoint,

		float maxThrust, const glm::vec3& thrustPoint
	)
	{
		inertia.mass = mass;
		inertia.momentOfInertia = momentOfInertia;
		inertia.nosePos = -centerOfMass;

		hStab.orientation = glm::angleAxis(glm::radians(hStabIncidenceAngleDeg),
			glm::vec3{1, 0, 0});
		hStab.area = hStabArea;
		hStab.liftCoefConst = hStabLiftCoefConst;
		float hStabCriticalAngleNegativeRad = glm::radians(hStabCriticalAngleNegativeDeg);
		float hStabCriticalAnglePositiveRad = glm::radians(hStabCriticalAnglePositiveDeg);
		hStab.liftCoefDeriv = adjustLiftCoefDeriv(hStabLiftCoefDeriv, hStabCriticalAngleNegativeRad,
			hStabCriticalAnglePositiveRad);
		hStab.normalForceCoef = hStabNormalForceCoef;
		hStab.criticalAngleNegativeRad = hStabCriticalAngleNegativeRad;
		hStab.criticalAnglePositiveRad = hStabCriticalAnglePositiveRad;
		hStab.liftPoint = hStabLiftPoint - centerOfMass;
		hStab.normalForcePoint = hStabNormalForcePoint - centerOfMass;
		hStab.ctrlArea = elevatorArea;
		hStab.ctrlLiftCoefDeriv = elevatorLiftCoefDeriv;
		hStab.ctrlMinAngleRad = glm::radians(elevatorMinAngleDeg);
		hStab.ctrlMaxAngleRad = glm::radians(elevatorMaxAngleDeg);
		hStab.ctrlLiftPoint = elevatorForcePoint - centerOfMass;

		vStab.orientation = glm::angleAxis(glm::radians(vStabIncidenceAngleDeg),
			glm::vec3{1, 0, 0});
		vStab.orientation = glm::angleAxis(glm::radians(-90.0f), glm::vec3{0, 0, 1}) *
			vStab.orientation;
		vStab.area = vStabArea;
		vStab.liftCoefConst = vStabLiftCoefConst;
		float vStabCriticalAngleNegativeRad = glm::radians(vStabCriticalAngleNegativeDeg);
		float vStabCriticalAnglePositiveRad = glm::radians(vStabCriticalAnglePositiveDeg);
		vStab.liftCoefDeriv = adjustLiftCoefDeriv(vStabLiftCoefDeriv, vStabCriticalAngleNegativeRad,
			vStabCriticalAnglePositiveRad);
		vStab.normalForceCoef = vStabNormalForceCoef;
		vStab.criticalAngleNegativeRad = vStabCriticalAngleNegativeRad;
		vStab.criticalAnglePositiveRad = vStabCriticalAnglePositiveRad;
		vStab.liftPoint = vStabLiftPoint - centerOfMass;
		vStab.normalForcePoint = vStabNormalForcePoint - centerOfMass;
		vStab.ctrlArea = rudderArea;
		vStab.ctrlLiftCoefDeriv = rudderLiftCoefDeriv;
		vStab.ctrlMinAngleRad = -glm::radians(rudderMaxAngleDeg);
		vStab.ctrlMaxAngleRad = glm::radians(rudderMaxAngleDeg);
		vStab.ctrlLiftPoint = rudderForcePoint - centerOfMass;

		leftWing.orientation = glm::angleAxis(glm::radians(wingsIncidenceAngleDeg),
			glm::vec3{1, 0, 0});
		leftWing.area = wingsArea / 2;
		leftWing.liftCoefConst = wingsLiftCoefConst;
		float leftWingCriticalAngleNegativeRad = glm::radians(wingsCriticalAngleNegativeDeg);
		float leftWingCriticalAnglePositiveRad = glm::radians(wingsCriticalAnglePositiveDeg);
		leftWing.liftCoefDeriv = adjustLiftCoefDeriv(wingsLiftCoefDeriv,
			leftWingCriticalAngleNegativeRad, leftWingCriticalAnglePositiveRad);
		leftWing.normalForceCoef = wingsNormalForceCoef;
		leftWing.criticalAngleNegativeRad = leftWingCriticalAngleNegativeRad;
		leftWing.criticalAnglePositiveRad = leftWingCriticalAnglePositiveRad;
		leftWing.liftPoint = rightWingLiftPoint - centerOfMass;
		leftWing.liftPoint.x *= -1;
		leftWing.normalForcePoint = rightWingNormalForcePoint - centerOfMass;
		leftWing.normalForcePoint.x *= -1;
		leftWing.ctrlArea = aileronsArea / 2;
		leftWing.ctrlLiftCoefDeriv = aileronsLiftCoefDeriv;
		leftWing.ctrlMinAngleRad = -glm::radians(aileronsMaxAngleDeg);
		leftWing.ctrlMaxAngleRad = glm::radians(aileronsMaxAngleDeg);
		leftWing.ctrlLiftPoint = rightAileronForcePoint - centerOfMass;
		leftWing.ctrlLiftPoint.x *= -1;

		rightWing.orientation = glm::angleAxis(glm::radians(wingsIncidenceAngleDeg),
			glm::vec3{1, 0, 0});
		rightWing.area = wingsArea / 2;
		rightWing.liftCoefConst = wingsLiftCoefConst;
		float rightWingCriticalAngleNegativeRad = glm::radians(wingsCriticalAngleNegativeDeg);
		float rightWingCriticalAnglePositiveRad = glm::radians(wingsCriticalAnglePositiveDeg);
		rightWing.liftCoefDeriv = adjustLiftCoefDeriv(wingsLiftCoefDeriv,
			rightWingCriticalAngleNegativeRad, rightWingCriticalAnglePositiveRad);
		rightWing.normalForceCoef = wingsNormalForceCoef;
		rightWing.criticalAngleNegativeRad = rightWingCriticalAngleNegativeRad;
		rightWing.criticalAnglePositiveRad = rightWingCriticalAnglePositiveRad;
		rightWing.liftPoint = rightWingLiftPoint - centerOfMass;
		rightWing.normalForcePoint = rightWingNormalForcePoint - centerOfMass;
		rightWing.ctrlArea = aileronsArea / 2;
		rightWing.ctrlLiftCoefDeriv = aileronsLiftCoefDeriv;
		rightWing.ctrlMinAngleRad = -glm::radians(aileronsMaxAngleDeg);
		rightWing.ctrlMaxAngleRad = glm::radians(aileronsMaxAngleDeg);
		rightWing.ctrlLiftPoint = rightAileronForcePoint - centerOfMass;

		fuselage.frontArea = fuselageFrontArea;
		fuselage.frontDragCoef = fuselageFrontDragCoef;
		fuselage.frontDragPoint = fuselageFrontDragPoint - centerOfMass;
		fuselage.sideArea = fuselageSideArea;
		fuselage.sideDragCoef = fuselageSideDragCoef;
		fuselage.sideDragPoint = fuselageSideDragPoint - centerOfMass;

		propulsion.maxThrust = maxThrust;
		propulsion.thrustPoint = thrustPoint;
	}

	float AirplaneParams::adjustLiftCoefDeriv(float liftCoefDeriv, float criticalAngleNegativeRad,
		float criticalAnglePositiveRad)
	{
		return liftCoefDeriv - (glm::sin(2 * criticalAnglePositiveRad) -
			glm::sin(2 * criticalAngleNegativeRad)) / (criticalAnglePositiveRad -
			criticalAngleNegativeRad);
	}
}
