#pragma once

#include "common/airplaneType.hpp"
#include "common/state.hpp"
#include "common/terrains/maps/map.hpp"

#include <glm/glm.hpp>

#include <random>

namespace Physics
{
	class Spawner
	{
	public:
		Spawner(const Common::Terrains::Map& map);
		Common::State spawn(Common::AirplaneType airplaneType);

	private:
		const Common::Terrains::Map& m_map;
		std::mt19937 m_generator{};
	};
}
