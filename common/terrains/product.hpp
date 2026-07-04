#pragma once

#include "common/terrains/terrain.hpp"

#include <memory>

namespace Common::Terrains
{
	class Product : public Terrain
	{
	public:
		Product(std::unique_ptr<Terrain> left, std::unique_ptr<Terrain> right);
		virtual ~Product() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		std::unique_ptr<Terrain> m_left{};
		std::unique_ptr<Terrain> m_right{};
	};
}
