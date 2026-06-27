#pragma once

#include <cstddef>

namespace Common
{
	inline constexpr int airplaneTypeCount = 2;

	enum class AirplaneTypeName
	{
		mustang,
		jw1
	};

	unsigned char toUChar(AirplaneTypeName airplaneTypeName);
	AirplaneTypeName fromUChar(unsigned char airplaneTypeName);

	constexpr std::size_t toSizeT(AirplaneTypeName airplaneTypeName)
	{
		return static_cast<std::size_t>(airplaneTypeName);
	}
}
