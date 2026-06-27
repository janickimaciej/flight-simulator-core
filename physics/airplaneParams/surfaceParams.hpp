#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Physics
{
	struct SurfaceParams
	{
		glm::quat orientation{};

		float area{};
		float liftCoefConst{};
		float liftCoefDeriv{};
		float normalForceCoef{};
		float criticalAngleNegativeRad{};
		float criticalAnglePositiveRad{};
		glm::vec3 liftPoint{};
		glm::vec3 normalForcePoint{};

		float ctrlArea{};
		float ctrlLiftCoefDeriv{};
		float ctrlMinAngleRad{};
		float ctrlMaxAngleRad{};
		glm::vec3 ctrlLiftPoint{};
	};
}
