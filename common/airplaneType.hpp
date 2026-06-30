#pragma once

#include <cstddef>

namespace Common
{
	inline constexpr int airplaneTypeCount = 2;

	enum class AirplaneType
	{
		mustang,
		jw1
	};

	unsigned char toUChar(AirplaneType airplaneType);
	AirplaneType fromUChar(unsigned char airplaneType);

	constexpr std::size_t toSizeT(AirplaneType airplaneType)
	{
		return static_cast<std::size_t>(airplaneType);
	}
}
