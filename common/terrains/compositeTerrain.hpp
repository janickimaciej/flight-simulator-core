#pragma once

#include "common/terrains/terrain.hpp"

#include <memory>
#include <vector>

namespace Common::Terrains
{
	class CompositeTerrain : public Terrain
	{
	public:
		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;
		virtual ~CompositeTerrain() = default;

	protected:
		std::vector<std::unique_ptr<Terrain>> m_elements{};
	};
}
