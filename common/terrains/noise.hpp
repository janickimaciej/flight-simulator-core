#pragma once

#include "common/config.hpp"
#include "common/noises/noise.hpp"
#include "common/terrains/terrain.hpp"

#include <memory>

namespace Common::Terrains
{
	class Noise : public Terrain
	{
	public:
		Noise(const std::shared_ptr<Common::Noise<noisePeriodExponent>>& noise, float length,
			float amplitude, float offset);
		virtual ~Noise() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		float m_frequency{};
		float m_amplitude{};
		float m_offset{};
		std::shared_ptr<Common::Noise<noisePeriodExponent>> m_noise{};
	};
}
