#pragma once

#include "common/terrains/terrain.hpp"

#include <memory>

namespace Common::Terrains::Maps
{
	std::unique_ptr<Terrain> sea();
	std::unique_ptr<Terrain> island();
}
