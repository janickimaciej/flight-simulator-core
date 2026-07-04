#include "common/terrains/constant.hpp"

namespace Common::Terrains
{
	Constant::Constant(float value) :
		m_value{value}
	{ }

	float Constant::height(float x, float z) const
	{
		return m_value;
	}

	float Constant::heightDerivX(float x, float z) const
	{
		return 0;
	}

	float Constant::heightDerivZ(float x, float z) const
	{
		return 0;
	}
}
