#include "physics/collisions/maps/map.hpp"

#include "physics/collisions/maps/islandMap.hpp"

namespace Physics::Collisions
{
	float Map::height(float x, float z) const
	{
		const Common::Terrains::Terrain& highestTerrain = getHighestTerrain(x, z);
		return highestTerrain.height(x, z);
	}

	float Map::heightDerivX(float x, float z) const
	{
		const Common::Terrains::Terrain& highestTerrain = getHighestTerrain(x, z);
		return highestTerrain.heightDerivX(x, z);
	}

	float Map::heightDerivZ(float x, float z) const
	{
		const Common::Terrains::Terrain& highestTerrain = getHighestTerrain(x, z);
		return highestTerrain.heightDerivZ(x, z);
	}

	std::unique_ptr<Map> Map::get(Common::MapName name)
	{
		switch (name)
		{
			case Common::MapName::island:
				return std::make_unique<IslandMap>();
		}
		return {};
	}
}
