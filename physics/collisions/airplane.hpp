#pragma once

#include "physics/collisions/ellipsoid.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Physics::Collisions
{
	struct Airplane
	{
		Ellipsoid ellipsoid{};
		std::array<glm::vec3, 6> points{};
	};
}
