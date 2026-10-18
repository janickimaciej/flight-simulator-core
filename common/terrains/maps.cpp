#include "common/terrains/maps.hpp"

#include "common/config.hpp"
#include "common/noises/perlinNoise.hpp"
#include "common/terrains/constant.hpp"
#include "common/terrains/noise.hpp"
#include "common/terrains/operators.hpp"
#include "common/terrains/plateau.hpp"

#include <glm/glm.hpp>

namespace Common::Terrains::Maps
{
	std::unique_ptr<Terrain> sea()
	{
		return std::make_unique<Constant>(waterLevel);
	}

	std::unique_ptr<Terrain> island()
	{
		static constexpr float islandRadius = 10000.0f;
		static constexpr glm::vec2 islandCenter{0, 0};
		static constexpr float smallIslandRadius = 2000.0f;
		static constexpr glm::vec2 smallIslandCenter{16000.0f, 14000.0f};
		static constexpr float maxLength = 6000.0f;
		static constexpr float maxAmplitude = 4000.0f;
		auto noise = std::make_shared<PerlinNoise<noisePeriodExponent>>(347);
		return (std::make_unique<Plateau>(0.0003f, islandRadius, islandCenter) +
			0.5f * std::make_unique<Plateau>(0.0006f, smallIslandRadius, smallIslandCenter)) *
			(std::make_unique<Noise>(noise, maxLength, maxAmplitude, 0.0f) +
			std::make_unique<Noise>(noise, maxLength / 2.0f, maxAmplitude / 2.0f, 0.0f) +
			std::make_unique<Noise>(noise, maxLength / 4.0f, maxAmplitude / 4.0f, 0.0f) +
			std::make_unique<Noise>(noise, maxLength / 8.0f, maxAmplitude / 8.0f, 0.0f) +
			std::make_unique<Noise>(noise, maxLength / 16.0f, maxAmplitude / 16.0f, 0.0f) +
			std::make_unique<Noise>(noise, maxLength / 32.0f, maxAmplitude / 32.0f, 0.0f) +
			std::make_unique<Noise>(noise, maxLength / 64.0f, maxAmplitude / 64.0f, 0.0f)) +
			-1000.0f;
	}
}
