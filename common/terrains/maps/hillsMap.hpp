#pragma once

#include "common/terrains/maps/map.hpp"

namespace Common::Terrains
{
	class HillsMap : public Map
	{
	public:
		HillsMap();
		virtual float getMaxHeight() const override;
		virtual ~HillsMap() = default;
	};
}
