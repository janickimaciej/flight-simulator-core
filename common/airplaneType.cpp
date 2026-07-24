#include "common/airplaneType.hpp"

namespace Common
{
	unsigned char toUChar(AirplaneType airplaneType)
	{
		return static_cast<unsigned char>(airplaneType);
	}

	AirplaneType fromUChar(unsigned char airplaneType)
	{
		return static_cast<AirplaneType>(airplaneType);
	}
}
