#include "common/maps/map.hpp"

#include <utility>

namespace Common::Maps
{
	const Terrains::Terrain& Map::terrain() const
	{
		return *m_terrain;
	}

	float Map::getLengthX() const
	{
		return m_lengthX;
	}

	float Map::getLengthZ() const
	{
		return m_lengthZ;
	}

	float Map::getSpacingX() const
	{
		return m_spacingX;
	}

	float Map::getSpacingZ() const
	{
		return m_spacingZ;
	}

	bool Map::isOutside(const glm::vec3& pos) const
	{
		return pos.x < 0 || pos.x > m_lengthX || pos.z < 0 || pos.z > m_lengthZ;
	}

	Map::Map(float lengthX, float lengthZ, float spacingX, float spacingZ) :
		m_lengthX{lengthX},
		m_lengthZ{lengthZ},
		m_spacingX{spacingX},
		m_spacingZ{spacingZ}
	{ }

	void Map::setTerrain(std::unique_ptr<Terrains::Terrain> terrain)
	{
		m_terrain = std::move(terrain);
	}
}
