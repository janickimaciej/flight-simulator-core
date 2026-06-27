#include "common/terrains/waveZ.hpp"

#include <glm/gtc/constants.hpp>

#include <cmath>

namespace Common::Terrains
{
	WaveZ::WaveZ(float amplitude, float length, float phaseRad) :
		m_amplitude{amplitude},
		m_length{length},
		m_phaseRad{phaseRad}
	{ }

	float WaveZ::height(float, float z) const
	{
		return m_amplitude * std::sin(2 * glm::pi<float>() * z / m_length + m_phaseRad);
	}

	float WaveZ::heightDerivX(float, float) const
	{
		return 0;
	}

	float WaveZ::heightDerivZ(float, float z) const
	{
		return 2 * glm::pi<float>() * m_amplitude / m_length *
			std::cos(2 * glm::pi<float>() * z / m_length + m_phaseRad);
	}
}
