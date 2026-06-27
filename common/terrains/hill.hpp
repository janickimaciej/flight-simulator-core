#pragma once

#include "common/terrains/terrain.hpp"

namespace Common::Terrains
{
	class Hill : public Terrain
	{
	public:
		Hill(float height, float radius, float centerX, float centerZ);

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		float m_height{};
		float m_radius{};
		float m_centerX{};
		float m_centerZ{};
	};
}
