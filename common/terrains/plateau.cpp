#include "common/terrains/plateau.hpp"

#include <cmath>

namespace Common::Terrains
{
	Plateau::Plateau(float steepness, float radius, const glm::vec2& center) :
		m_steepness{steepness},
		m_radius{radius},
		m_center{center}
	{ }

	float Plateau::height(float x, float z) const
	{
		float distance = distanceFromCenter(x, z);
		float softsignArg = -m_steepness * (distance - m_radius);
		return 0.5f * softsignArg / (1.0f + std::abs(softsignArg)) + 0.5f;
	}

	float Plateau::heightDerivX(float x, float z) const
	{
		float distance = distanceFromCenter(x, z);
		if (distance < 1e-9f) return 0;
		float softsignArg = -m_steepness * (distance - m_radius);
		return -m_steepness * 0.5f * (x - m_center.x) /
			(distance * std::pow(1.0f + std::abs(softsignArg), 2.0f));
	}

	float Plateau::heightDerivZ(float x, float z) const
	{
		float distance = distanceFromCenter(x, z);
		if (distance < 1e-9f) return 0;
		float softsignArg = -m_steepness * (distance - m_radius);
		return -m_steepness * 0.5f * (z - m_center.y) /
			(distance * std::pow(1.0f + std::abs(softsignArg), 2.0f));
	}

	float Plateau::distanceFromCenter(float x, float z) const
	{
		return glm::length(glm::vec2{x, z} - m_center);
	}
}
