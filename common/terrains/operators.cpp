#include "common/terrains/operators.hpp"

#include "common/terrains/constant.hpp"
#include "common/terrains/product.hpp"
#include "common/terrains/sum.hpp"

#include <utility>

namespace Common::Terrains
{
	std::unique_ptr<Terrain> operator+(std::unique_ptr<Terrain> left,
		std::unique_ptr<Terrain> right)
	{
		return std::make_unique<Sum>(std::move(left), std::move(right));
	}

	std::unique_ptr<Terrain> operator+(std::unique_ptr<Terrain> left, float constant)
	{
		return std::move(left) + std::make_unique<Constant>(constant);
	}

	std::unique_ptr<Terrain> operator+(float constant, std::unique_ptr<Terrain> right)
	{
		return std::make_unique<Constant>(constant) + std::move(right);
	}

	std::unique_ptr<Terrain> operator*(std::unique_ptr<Terrain> left,
		std::unique_ptr<Terrain> right)
	{
		return std::make_unique<Product>(std::move(left), std::move(right));
	}

	std::unique_ptr<Terrain> operator*(std::unique_ptr<Terrain> left, float constant)
	{
		return std::move(left) * std::make_unique<Constant>(constant);
	}

	std::unique_ptr<Terrain> operator*(float constant, std::unique_ptr<Terrain> right)
	{
		return std::make_unique<Constant>(constant) * std::move(right);
	}
}
