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
		return pos.x < -m_lengthX / 2.0f || pos.x > m_lengthX / 2.0f ||
			pos.z < -m_lengthZ / 2.0f || pos.z > m_lengthZ / 2.0f;
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
