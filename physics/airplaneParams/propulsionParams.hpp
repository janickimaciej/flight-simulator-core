#pragma once

#include <glm/glm.hpp>

namespace Physics
{
	struct PropulsionParams
	{
		float maxThrust{};
		glm::vec3 thrustPoint{};
	};
}
