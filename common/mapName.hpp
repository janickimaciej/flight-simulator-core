#pragma once

#include <cstddef>

namespace Common
{
	inline constexpr int mapCount = 1;

	enum class MapName
	{
		island
	};

	std::size_t toSizeT(MapName map);
}
