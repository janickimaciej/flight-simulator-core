#pragma once

#include "common/maps/map.hpp"

namespace Common::Maps
{
	class AirportMap : public Map
	{
	public:
		AirportMap();
		virtual ~AirportMap() = default;

		virtual float getMaxHeight() const override;
	};
}
