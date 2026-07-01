#include "physics/spawner.hpp"

#include "common/airplaneType.hpp"
#include "common/state.hpp"
#include "common/terrains/maps/map.hpp"
#include "physics/airplaneDefinitions.hpp"

#include <glm/glm.hpp>

#include <ctime>

namespace Physics
{
	Spawner::Spawner(const Common::Terrains::Map& map) :
		m_map{map},
		m_generator{static_cast<unsigned int>(std::time(nullptr))}
	{ }

	Common::State Spawner::spawn(Common::AirplaneType airplaneType)
	{
		Common::State state{};

		std::uniform_real_distribution<float> xFloatDistribution(0, m_map.getLengthX());
		std::uniform_real_distribution<float> zFloatDistribution(0, m_map.getLengthZ());

		state.pos.x = xFloatDistribution(m_generator);
		static constexpr float heightMargin = 50;
		state.pos.y = m_map.getMaxHeight() + heightMargin;
		state.pos.z = zFloatDistribution(m_generator);

		static constexpr float eps = 0.01f;
		if (std::abs(state.pos.x) < eps && std::abs(state.pos.z) < eps)
		{
			state.pos.x = 1;
		}

		state.setOrientation(glm::normalize(glm::vec3
			{
				state.pos.x - m_map.getLengthX() / 2,
				0,
				state.pos.z - m_map.getLengthZ() / 2
			}));

		state.velocity = airplaneDefinitions[Common::toSizeT(airplaneType)].initialVelocity;

		return state;
	}
}
