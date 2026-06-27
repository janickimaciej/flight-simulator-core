#include "physics/atmosphere.hpp"

#include <algorithm>

namespace Physics
{
	float Atmosphere::airDensity(float height)
	{
		static constexpr float zeroAirDensityHeight = 44300;
		return std::max(seaLevelAirDensity * (1 - height/zeroAirDensityHeight), 0.0f);
	}
}
