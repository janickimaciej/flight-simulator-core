#include "common/terrains/waveX.hpp"

#include <glm/gtc/constants.hpp>

#include <cmath>

namespace Common::Terrains
{
	WaveX::WaveX(float amplitude, float length, float phaseRad) :
		m_amplitude{amplitude},
		m_length{length},
		m_phaseRad{phaseRad}
	{ }

	float WaveX::height(float x, float) const
	{
		return m_amplitude * std::sin(2 * glm::pi<float>() * x / m_length + m_phaseRad);
	}

	float WaveX::heightDerivX(float x, float) const
	{
		return 2 * glm::pi<float>() * m_amplitude / m_length *
			std::cos(2 * glm::pi<float>() * x / m_length + m_phaseRad);
	}

	float WaveX::heightDerivZ(float, float) const
	{
		return 0;
	}
}
