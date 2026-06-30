#include "common/mapName.hpp"

#include <cstddef>

namespace Common
{
	std::size_t toSizeT(MapName map)
	{
		return static_cast<std::size_t>(map);
	}
}
