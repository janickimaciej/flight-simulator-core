#pragma once

#include "common/terrains/maps.hpp"
#include "common/terrains/terrain.hpp"
#include "physics/collisions/maps/map.hpp"

#include <memory>

namespace Physics::Collisions
{
	class IslandMap : public Map
	{
	public:
		virtual ~IslandMap() = default;

	private:
		std::unique_ptr<Common::Terrains::Terrain> m_sea = Common::Terrains::Maps::sea();
		std::unique_ptr<Common::Terrains::Terrain> m_land = Common::Terrains::Maps::island();

		const Common::Terrains::Terrain& getHighestTerrain(float x, float z) const;
	};
}
