#pragma once

#include "common/mapName.hpp"
#include "common/terrains/maps.hpp"
#include "common/terrains/terrain.hpp"

#include <memory>

namespace Physics::Collisions
{
	class Map : public Common::Terrains::Terrain
	{
	public:
		virtual ~Map() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

		static std::unique_ptr<Map> get(Common::MapName name);

	private:
		virtual const Common::Terrains::Terrain& getHighestTerrain(float x, float z) const = 0;
	};
}
