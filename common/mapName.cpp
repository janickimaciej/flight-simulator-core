#include "common/mapName.hpp"

#include <cstddef>

namespace Common
{
	std::size_t toSizeT(MapName mapName)
	{
		return static_cast<std::size_t>(mapName);
	}
}
