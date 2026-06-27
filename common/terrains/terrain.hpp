#pragma once

namespace Common::Terrains
{
	class Terrain
	{
	public:
		virtual float height(float x, float z) const = 0;
		virtual float heightDerivX(float x, float z) const = 0;
		virtual float heightDerivZ(float x, float z) const = 0;
		virtual ~Terrain() = default;
	};
}
