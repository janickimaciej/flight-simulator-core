#pragma once

#include "common/terrains/terrain.hpp"
#include "common/valueNoise.hpp"

namespace Common::Terrains
{
	class ValueNoise : public Terrain
	{
	public:
		ValueNoise(float frequency, float amplitude, float offset);

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		float m_frequency{};
		float m_amplitude{};
		float m_offset{};
		Common::ValueNoise<8> valueNoise{347};
	};
}
