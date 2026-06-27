#include "common/terrains/hill.hpp"

#include <cmath>

namespace Common::Terrains
{
	Hill::Hill(float height, float radius, float centerX, float centerZ) :
		m_height{height},
		m_radius{radius},
		m_centerX{centerX},
		m_centerZ{centerZ}
	{ }

	float Hill::height(float x, float z) const
	{
		return m_height * std::exp(-4 * ((x - m_centerX) * (x - m_centerX) +
			(z - m_centerZ) * (z - m_centerZ)) / (m_radius * m_radius));
	}

	float Hill::heightDerivX(float x, float z) const
	{
		return -8 * m_height * std::exp(-4 * ((x - m_centerX) * (x - m_centerX) +
			(z - m_centerZ) * (z - m_centerZ)) / (m_radius * m_radius)) *
			(x - m_centerX) / (m_radius * m_radius);
	}

	float Hill::heightDerivZ(float x, float z) const
	{
		return -8 * m_height * std::exp(-4 * ((x - m_centerX) * (x - m_centerX) +
			(z - m_centerZ) * (z - m_centerZ)) / (m_radius * m_radius)) *
			(z - m_centerZ) / (m_radius * m_radius);
	}
}
