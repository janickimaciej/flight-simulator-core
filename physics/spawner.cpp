#include "physics/spawner.hpp"

#include "physics/airplaneDefinitions.hpp"

#include <glm/glm.hpp>

#include <cmath>

namespace Physics
{
	Common::State Spawner::spawn(Common::AirplaneType airplaneType)
	{
		Common::State state{};

		static constexpr float radius = 30000;
		std::uniform_real_distribution<float> angleRadDistribution(0, glm::radians(360.0f));
		float angleRad = angleRadDistribution(m_generator);
		state.pos.x = radius * std::cos(angleRad);
		state.pos.z = radius * std::sin(angleRad);

		static constexpr float height = 5000;
		state.pos.y = height;

		state.setOrientation(glm::normalize(glm::vec3{state.pos.x, 0, state.pos.z}));

		state.velocity = airplaneDefinitions[Common::toSizeT(airplaneType)].initialVelocity;

		return state;
	}
}
