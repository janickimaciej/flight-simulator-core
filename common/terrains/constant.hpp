#pragma once

#include "common/terrains/terrain.hpp"

namespace Common::Terrains
{
	class Constant : public Terrain
	{
	public:
		Constant(float value);
		virtual ~Constant() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		float m_value{};
	};
}
