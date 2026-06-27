#include "common/terrains/compositeTerrain.hpp"

namespace Common::Terrains
{
	float CompositeTerrain::height(float x, float z) const
	{
		float height = 0;
		for (const std::unique_ptr<Terrain>& element : m_elements)
		{
			height += element->height(x, z);
		}
		return height;
	}

	float CompositeTerrain::heightDerivX(float x, float z) const
	{
		float heightDerivX = 0;
		for (const std::unique_ptr<Terrain>& element : m_elements)
		{
			heightDerivX += element->heightDerivX(x, z);
		}
		return heightDerivX;
	}

	float CompositeTerrain::heightDerivZ(float x, float z) const
	{
		float heightDerivZ = 0;
		for (const std::unique_ptr<Terrain>& element : m_elements)
		{
			heightDerivZ += element->heightDerivZ(x, z);
		}
		return heightDerivZ;
	}
}
