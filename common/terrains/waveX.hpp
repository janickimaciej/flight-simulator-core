#pragma once

#include "common/terrains/terrain.hpp"

namespace Common::Terrains
{
	class WaveX : public Terrain
	{
	public:
		WaveX(float amplitude, float length, float phaseRad);

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		float m_amplitude{};
		float m_length{};
		float m_phaseRad{};
	};
}
