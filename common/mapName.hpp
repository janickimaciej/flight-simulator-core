#pragma once

#include <cstddef>

namespace Common
{
	inline constexpr int mapCount = 2;

	enum class MapName
	{
		airport,
		island
	};

	std::size_t toSizeT(MapName map);
}
