#include "physics/spawner.hpp"

#include "physics/airplaneDefinitions.hpp"

#include <glm/glm.hpp>

#include <cmath>
#include <ctime>

namespace Physics
{
	Spawner::Spawner(const Common::Maps::Map& map) :
		m_map{map},
		m_generator{static_cast<unsigned int>(std::time(nullptr))}
	{ }

	Common::State Spawner::spawn(Common::AirplaneType airplaneType)
	{
		Common::State state{};

		std::uniform_real_distribution<float> xFloatDistribution(-m_map.getLengthX() / 2.0f,
			m_map.getLengthX() / 2.0f);
		std::uniform_real_distribution<float> zFloatDistribution(-m_map.getLengthZ() / 2.0f,
			m_map.getLengthZ() / 2.0f);

		state.pos.x = xFloatDistribution(m_generator);
		static constexpr float heightMargin = 50;
		state.pos.y = m_map.getMaxHeight() + heightMargin;
		state.pos.z = zFloatDistribution(m_generator);

		static constexpr float eps = 0.01f;
		if (std::abs(state.pos.x) < eps && std::abs(state.pos.z) < eps)
		{
			state.pos.x = 1;
		}

		state.setOrientation(glm::normalize(glm::vec3{state.pos.x, 0, state.pos.z}));

		state.velocity = airplaneDefinitions[Common::toSizeT(airplaneType)].initialVelocity;

		return state;
	}
}
