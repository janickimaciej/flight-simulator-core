#pragma once

#include <glm/glm.hpp>

namespace Physics::Collisions
{
	struct Ellipsoid
	{
		glm::vec3 center{};
		float semiaxisX{};
		float semiaxisY{};
		float semiaxisZ{};
	};
}
