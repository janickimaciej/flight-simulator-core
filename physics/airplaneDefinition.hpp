#pragma once

#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/collisions/airplane.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	struct AirplaneDefinition
	{
		AirplaneParams params;
		glm::vec3 initialVelocity{};
		glm::vec3 muzzlePos{};
		glm::vec3 muzzleVelocity{};
		Collisions::Airplane collisionModel{};
		int initialHP{};
	};
}
