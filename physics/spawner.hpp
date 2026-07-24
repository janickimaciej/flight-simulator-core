#pragma once

#include "common/airplaneType.hpp"
#include "common/maps/map.hpp"
#include "common/state.hpp"

#include <random>

namespace Physics
{
	class Spawner
	{
	public:
		Spawner(const Common::Maps::Map& map);

		Common::State spawn(Common::AirplaneType airplaneType);

	private:
		const Common::Maps::Map& m_map;
		std::mt19937 m_generator{};
	};
}
