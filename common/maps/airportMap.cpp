#include "common/maps/airportMap.hpp"

namespace Common::Maps
{
	// TODO: correct values
	static constexpr float lengthX = 40000;
	static constexpr float lengthZ = 40000;
	static constexpr float spacingX = 50;
	static constexpr float spacingZ = 50;

	AirportMap::AirportMap() :
		Map{lengthX, lengthZ, spacingX, spacingZ}
	{
		// TODO setTerrain()
	}

	float AirportMap::getMaxHeight() const
	{
		return 0;
	}
}
