#include "common/terrains/maps/map.hpp"

#include <glm/glm.hpp>

namespace Common::Terrains
{
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

	bool Map::isOutside(const glm::vec3& position) const
	{
		return position.x < 0 || position.x > m_lengthX || position.z < 0 || position.z > m_lengthZ;
	}

	Map::Map(float lengthX, float lengthZ, float spacingX, float spacingZ) :
		m_lengthX{lengthX},
		m_lengthZ{lengthZ},
		m_spacingX{spacingX},
		m_spacingZ{spacingZ}
	{ }
}
