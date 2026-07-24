#include "common/terrains/constant.hpp"

namespace Common::Terrains
{
	Constant::Constant(float value) :
		m_value{value}
	{ }

	float Constant::height(float, float) const
	{
		return m_value;
	}

	float Constant::heightDerivX(float, float) const
	{
		return 0;
	}

	float Constant::heightDerivZ(float, float) const
	{
		return 0;
	}
}
