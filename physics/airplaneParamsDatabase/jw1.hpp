#pragma once

#include "common/airplaneCentersOfMass.hpp"
#include "common/airplaneType.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"

#include <glm/glm.hpp>

#include <cstddef>

namespace Physics
{
	namespace database::jw1
	{
		inline constexpr float mass = 20000;
		inline constexpr glm::mat3 momentOfInertia
		{
			247000, 0, 0,
			0, 271000, -1230,
			0, -1230, 29800
		};
		inline constexpr glm::vec3 centerOfMass = Common::airplaneCentersOfMass[
			toSizeT(Common::AirplaneType::jw1)];

		inline constexpr float hStabIncidenceAngleDeg = 0;
		inline constexpr float hStabArea = 9.22f;
		inline constexpr float hStabLiftCoefConst = 0;
		inline constexpr float hStabLiftCoefDeriv = 3.82f;
		inline constexpr float hStabNormalForceCoef = 2;
		inline constexpr float hStabCriticalAngleNegativeDeg = -18;
		inline constexpr float hStabCriticalAnglePositiveDeg = 18;
		inline constexpr glm::vec3 hStabLiftPoint{0, 0, 18.2};
		inline constexpr glm::vec3 hStabNormalForcePoint{0, 0, 18.6};
		inline constexpr float elevatorArea = 9.22f; // area of the part of the hStab with elevator
		inline constexpr float elevatorLiftCoefDeriv = 0.4f;
		inline constexpr float elevatorMinAngleDeg = -15;
		inline constexpr float elevatorMaxAngleDeg = 15;
		inline constexpr glm::vec3 elevatorForcePoint{0, 0, 18.2};

		inline constexpr float vStabIncidenceAngleDeg = 0;
		inline constexpr float vStabArea = 7.74f;
		inline constexpr float vStabLiftCoefConst = 0;
		inline constexpr float vStabLiftCoefDeriv = 3.82f;
		inline constexpr float vStabNormalForceCoef = 2;
		inline constexpr float vStabCriticalAngleNegativeDeg = -18;
		inline constexpr float vStabCriticalAnglePositiveDeg = 18;
		inline constexpr glm::vec3 vStabLiftPoint{0, 1.31, 18.2};
		inline constexpr glm::vec3 vStabNormalForcePoint{0, 1.31, 18.8};
		inline constexpr float rudderArea = 7.43f; // area of the part of the vStab with rudder
		inline constexpr float rudderLiftCoefDeriv = 0.2f;
		inline constexpr float rudderMaxAngleDeg = 15;
		inline constexpr glm::vec3 rudderForcePoint{0, 1.31, 19.6};

		inline constexpr float wingsIncidenceAngleDeg = 0;
		inline constexpr float wingsArea = 55;
		inline constexpr float wingsLiftCoefConst = 0;
		inline constexpr float wingsLiftCoefDeriv = 3.82f;
		inline constexpr float wingsNormalForceCoef = 2;
		inline constexpr float wingsCriticalAngleNegativeDeg = -18;
		inline constexpr float wingsCriticalAnglePositiveDeg = 18;
		inline constexpr glm::vec3 rightWingLiftPoint{2.51, 0.68, 11.5};
		inline constexpr glm::vec3 rightWingNormalForcePoint{2.51, 0.68, 12.7};
		inline constexpr float aileronsArea = 10.9f; // area of the part of the wings with ailerons
		inline constexpr float aileronsLiftCoefDeriv = 0.2f;
		inline constexpr float aileronsMaxAngleDeg = 15;
		inline constexpr glm::vec3 rightAileronForcePoint{4.96, 0.45, 15.2};

		inline constexpr float fuselageFrontArea = 1.9f;
		inline constexpr float fuselageFrontDragCoef = 0.35f;
		inline constexpr glm::vec3 fuselageFrontDragPoint{0, 0, 0};
		inline constexpr float fuselageSideArea = 29.2f;
		inline constexpr float fuselageSideDragCoef = 0.59f;
		inline constexpr glm::vec3 fuselageSideDragPoint{0, 0, 8.55};

		inline constexpr float maxThrust = 130000;
		inline constexpr glm::vec3 thrustPoint{0, 0, 0.44};
	}

	inline const AirplaneParams jw1Params
	{
		database::jw1::mass, database::jw1::momentOfInertia,
		database::jw1::centerOfMass,

		database::jw1::hStabIncidenceAngleDeg, database::jw1::hStabArea,
		database::jw1::hStabLiftCoefConst, database::jw1::hStabLiftCoefDeriv,
		database::jw1::hStabNormalForceCoef, database::jw1::hStabCriticalAngleNegativeDeg,
		database::jw1::hStabCriticalAnglePositiveDeg, database::jw1::hStabLiftPoint,
		database::jw1::hStabNormalForcePoint, database::jw1::elevatorArea,
		database::jw1::elevatorLiftCoefDeriv, database::jw1::elevatorMinAngleDeg,
		database::jw1::elevatorMaxAngleDeg, database::jw1::elevatorForcePoint,

		database::jw1::vStabIncidenceAngleDeg, database::jw1::vStabArea,
		database::jw1::vStabLiftCoefConst, database::jw1::vStabLiftCoefDeriv,
		database::jw1::vStabNormalForceCoef, database::jw1::vStabCriticalAngleNegativeDeg,
		database::jw1::vStabCriticalAnglePositiveDeg, database::jw1::vStabLiftPoint,
		database::jw1::vStabNormalForcePoint, database::jw1::rudderArea,
		database::jw1::rudderLiftCoefDeriv, database::jw1::rudderMaxAngleDeg,
		database::jw1::rudderForcePoint,

		database::jw1::wingsIncidenceAngleDeg, database::jw1::wingsArea,
		database::jw1::wingsLiftCoefConst, database::jw1::wingsLiftCoefDeriv,
		database::jw1::wingsNormalForceCoef, database::jw1::wingsCriticalAngleNegativeDeg,
		database::jw1::wingsCriticalAnglePositiveDeg, database::jw1::rightWingLiftPoint,
		database::jw1::rightWingNormalForcePoint, database::jw1::aileronsArea,
		database::jw1::aileronsLiftCoefDeriv, database::jw1::aileronsMaxAngleDeg,
		database::jw1::rightAileronForcePoint,

		database::jw1::fuselageFrontArea, database::jw1::fuselageFrontDragCoef,
		database::jw1::fuselageFrontDragPoint, database::jw1::fuselageSideArea,
		database::jw1::fuselageSideDragCoef, database::jw1::fuselageSideDragPoint,

		database::jw1::maxThrust, database::jw1::thrustPoint
	};
}
