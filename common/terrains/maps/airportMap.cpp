#include "common/terrains/maps/airportMap.hpp"

namespace Common::Terrains
{
	// TODO: correct values
	static constexpr float lengthX = 20000;
	static constexpr float lengthZ = 20000;
	static constexpr float spacingX = 50;
	static constexpr float spacingZ = 50;

	AirportMap::AirportMap() :
		Map{lengthX, lengthZ, spacingX, spacingZ}
	{ }

	float AirportMap::getMaxHeight() const
	{
		return 0;
	}
}
