#pragma once

#include "common/terrains/terrain.hpp"

#include <memory>

namespace Common::Terrains
{
	std::unique_ptr<Terrain> operator+(std::unique_ptr<Terrain> left,
		std::unique_ptr<Terrain> right);
	std::unique_ptr<Terrain> operator+(std::unique_ptr<Terrain> left, float constant);
	std::unique_ptr<Terrain> operator+(float constant, std::unique_ptr<Terrain> right);

	std::unique_ptr<Terrain> operator*(std::unique_ptr<Terrain> left,
		std::unique_ptr<Terrain> right);
}
