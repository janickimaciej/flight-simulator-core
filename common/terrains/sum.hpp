#pragma once

#include "common/terrains/terrain.hpp"

#include <memory>

namespace Common::Terrains
{
	class Sum : public Terrain
	{
	public:
		Sum(std::unique_ptr<Terrain> left, std::unique_ptr<Terrain> right);
		virtual ~Sum() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		std::unique_ptr<Terrain> m_left{};
		std::unique_ptr<Terrain> m_right{};
	};
}
