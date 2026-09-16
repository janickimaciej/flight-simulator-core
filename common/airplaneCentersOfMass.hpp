#pragma once

#include "common/airplaneType.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Common
{
	inline constexpr std::array<glm::vec3, airplaneTypeCount> airplaneCentersOfMass
	{
		glm::vec3{0, 0, 4.15f},
		glm::vec3{0, 0, 12.5f}
	};
}
