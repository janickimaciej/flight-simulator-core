#pragma once

#include "common/terrains/terrain.hpp"

#include <glm/glm.hpp>

namespace Common::Terrains
{
	class Plateau : public Terrain
	{
	public:
		Plateau(float steepness, float radius, const glm::vec2& center);

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		float m_steepness{};
		float m_radius{};
		glm::vec2 m_center{};

		float distanceFromCenter(float x, float z) const;
	};
}
