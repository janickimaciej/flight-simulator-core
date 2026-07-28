#pragma once

#include "common/mapName.hpp"
#include "common/maps/islandMap.hpp"
#include "common/maps/map.hpp"

#include <array>
#include <memory>

namespace Common::Maps
{
	inline const std::array<std::unique_ptr<Map>, Common::mapCount> maps
	{
		std::make_unique<IslandMap>()
	};
}
