#include "common/terrains/product.hpp"

#include <utility>

namespace Common::Terrains
{
	Product::Product(std::unique_ptr<Terrain> left, std::unique_ptr<Terrain> right) :
		m_left{std::move(left)},
		m_right{std::move(right)}
	{ }

	float Product::height(float x, float z) const
	{
		return m_left->height(x, z) * m_right->height(x, z);
	}

	float Product::heightDerivX(float x, float z) const
	{
		return m_left->heightDerivX(x, z) * m_right->height(x, z) +
			m_left->height(x, z) * m_right->heightDerivX(x, z);
	}

	float Product::heightDerivZ(float x, float z) const
	{
		return m_left->heightDerivZ(x, z) * m_right->height(x, z) +
			m_left->height(x, z) * m_right->heightDerivZ(x, z);
	}
}
