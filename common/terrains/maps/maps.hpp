#pragma once

#include "common/mapName.hpp"
#include "common/terrains/maps/airportMap.hpp"
#include "common/terrains/maps/hillsMap.hpp"

#include <array>
#include <memory>

namespace Common::Terrains
{
	inline const std::array<std::unique_ptr<Map>, Common::mapCount> maps
	{
		std::make_unique<AirportMap>(),
		std::make_unique<HillsMap>()
	};
}
