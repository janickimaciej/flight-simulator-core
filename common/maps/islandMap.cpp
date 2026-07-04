#include "common/maps/islandMap.hpp"

#include "common/terrains/hill.hpp"
#include "common/terrains/operators.hpp"
#include "common/terrains/plateau.hpp"
#include "common/terrains/valueNoise.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Common::Maps
{
	static constexpr float lengthX = 40000;
	static constexpr float lengthZ = 40000;
	static constexpr float spacingX = 50;
	static constexpr float spacingZ = 50;

	IslandMap::IslandMap() :
		Map{lengthX, lengthZ, spacingX, spacingZ}
	{
		static constexpr glm::vec2 islandCenter{20000.0f, 20000.0f};
		static constexpr float islandRadius = 10000.0f;
		setTerrain(std::make_unique<Terrains::Plateau>(0.0003f, islandRadius, islandCenter) *
			(std::make_unique<Terrains::ValueNoise>(0.00012f, 4096.0f, 0.0f) +
			std::make_unique<Terrains::ValueNoise>(0.00025f, 2048.0f, 0.0f) +
			std::make_unique<Terrains::ValueNoise>(0.0005f, 1024.0f, 0.0f) +
			std::make_unique<Terrains::ValueNoise>(0.001f, 512.0f, 0.0f) +
			std::make_unique<Terrains::ValueNoise>(0.002f, 256.0f, 0.0f) +
			std::make_unique<Terrains::ValueNoise>(0.004f, 128.0f, 0.0f) +
			std::make_unique<Terrains::ValueNoise>(0.008f, 64.0f, 0.0f)) + -500.0f);
	}

	float IslandMap::getMaxHeight() const
	{
		return 8192;
	}
}
