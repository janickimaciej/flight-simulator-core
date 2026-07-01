#pragma once

#include <glm/glm.hpp>

namespace Physics
{
	struct InertiaParams
	{
		float mass{};
		glm::mat3 momentOfInertia{};
		glm::vec3 nosePos{};
	};
}
