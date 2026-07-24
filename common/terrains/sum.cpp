#include "common/terrains/sum.hpp"

#include <utility>

namespace Common::Terrains
{
	Sum::Sum(std::unique_ptr<Terrain> left, std::unique_ptr<Terrain> right) :
		m_left{std::move(left)},
		m_right{std::move(right)}
	{ }

	float Sum::height(float x, float z) const
	{
		return m_left->height(x, z) + m_right->height(x, z);
	}

	float Sum::heightDerivX(float x, float z) const
	{
		return m_left->heightDerivX(x, z) + m_right->heightDerivX(x, z);
	}

	float Sum::heightDerivZ(float x, float z) const
	{
		return m_left->heightDerivZ(x, z) + m_right->heightDerivZ(x, z);
	}
}
