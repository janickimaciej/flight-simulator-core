#pragma once

#include "common/maps/map.hpp"

namespace Common::Maps
{
	class IslandMap : public Map
	{
	public:
		IslandMap();
		virtual ~IslandMap() = default;

		virtual float getMaxHeight() const override;
	};
}
