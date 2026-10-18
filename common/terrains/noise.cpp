#include "common/terrains/noise.hpp"

namespace Common::Terrains
{
	Noise::Noise(const std::shared_ptr<Common::Noise<noisePeriodExponent>>& noise, float length,
		float amplitude, float offset) :
		m_noise{noise},
		m_frequency{1.0f / length},
		m_amplitude{amplitude},
		m_offset{offset}
	{ }

	float Noise::height(float x, float z) const
	{
		float normalizedHeight =
			m_noise->height(m_frequency * (x + m_offset), m_frequency * (z + m_offset));
		return normalizedHeight * m_amplitude;
	}

	float Noise::heightDerivX(float x, float z) const
	{
		float normalizedHeightDerivX = m_frequency *
			m_noise->heightDerivX(m_frequency * (x + m_offset), m_frequency * (z + m_offset));
		return normalizedHeightDerivX * m_amplitude;
	}

	float Noise::heightDerivZ(float x, float z) const
	{
		float normalizedHeightDerivZ = m_frequency *
			m_noise->heightDerivZ(m_frequency * (x + m_offset), m_frequency * (z + m_offset));
		return normalizedHeightDerivZ * m_amplitude;
	}
}
