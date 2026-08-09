#include "physics/collisions/maps/islandMap.hpp"

namespace Physics::Collisions
{
	const Common::Terrains::Terrain& IslandMap::getHighestTerrain(float x, float z) const
	{
		return m_land->height(x, z) > m_sea->height(x, z) ? *m_land : *m_sea;
	}
}
