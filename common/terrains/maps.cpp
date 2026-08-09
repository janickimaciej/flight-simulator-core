#include "common/terrains/maps.hpp"

#include "common/terrains/constant.hpp"
#include "common/terrains/operators.hpp"
#include "common/terrains/plateau.hpp"
#include "common/terrains/valueNoise.hpp"

#include <glm/glm.hpp>

namespace Common::Terrains::Maps
{
	std::unique_ptr<Terrain> sea()
	{
		float seaLevel = 0;
		return std::make_unique<Constant>(seaLevel);
	}

	std::unique_ptr<Terrain> island()
	{
		static constexpr float islandRadius = 10000.0f;
		static constexpr glm::vec2 islandCenter{0, 0};
		static constexpr float smallIslandRadius = 2000.0f;
		static constexpr glm::vec2 smallIslandCenter{16000.0f, 14000.0f};
		return (std::make_unique<Plateau>(0.0003f, islandRadius, islandCenter) +
			0.5f * std::make_unique<Plateau>(0.0006f, smallIslandRadius,
				smallIslandCenter)) *
			(std::make_unique<ValueNoise>(0.00012f, 4096.0f, 0.0f) +
			std::make_unique<ValueNoise>(0.00025f, 2048.0f, 0.0f) +
			std::make_unique<ValueNoise>(0.0005f, 1024.0f, 0.0f) +
			std::make_unique<ValueNoise>(0.001f, 512.0f, 0.0f) +
			std::make_unique<ValueNoise>(0.002f, 256.0f, 0.0f) +
			std::make_unique<ValueNoise>(0.004f, 128.0f, 0.0f) +
			std::make_unique<ValueNoise>(0.008f, 64.0f, 0.0f)) +
			-1000.0f;
	}
}
