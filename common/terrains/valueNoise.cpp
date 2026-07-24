#include "common/terrains/valueNoise.hpp"

namespace Common::Terrains
{
	ValueNoise::ValueNoise(float frequency, float amplitude, float offset) :
		m_frequency{frequency},
		m_amplitude{amplitude},
		m_offset{offset}
	{ }

	float ValueNoise::height(float x, float z) const
	{
		float normalizedHeight =
			m_valueNoise.height(m_frequency * (x + m_offset), m_frequency * (z + m_offset));
		return normalizedHeight * m_amplitude;
	}

	float ValueNoise::heightDerivX(float x, float z) const
	{
		float normalizedHeightDerivX = m_frequency *
			m_valueNoise.heightDerivX(m_frequency * (x + m_offset), m_frequency * (z + m_offset));
		return normalizedHeightDerivX * m_amplitude;
	}

	float ValueNoise::heightDerivZ(float x, float z) const
	{
		float normalizedHeightDerivZ = m_frequency *
			m_valueNoise.heightDerivZ(m_frequency * (x + m_offset), m_frequency * (z + m_offset));
		return normalizedHeightDerivZ * m_amplitude;
	}
}
