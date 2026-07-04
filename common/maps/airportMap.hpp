#pragma once

#include "common/maps/map.hpp"

namespace Common::Maps
{
	class AirportMap : public Map
	{
	public:
		AirportMap();
		virtual float getMaxHeight() const override;
		virtual ~AirportMap() = default;
	};
}
