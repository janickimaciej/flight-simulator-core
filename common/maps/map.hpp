#pragma once

#include "common/terrains/terrain.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Common::Maps
{
	class Map
	{
	public:
		virtual ~Map() = default;

		const Terrains::Terrain& terrain() const;
		float getLengthX() const;
		float getLengthZ() const;
		float getSpacingX() const;
		float getSpacingZ() const;
		virtual float getMaxHeight() const = 0;
		bool isOutside(const glm::vec3& pos) const;

	protected:
		Map(float lengthX, float lengthZ, float spacingX, float spacingZ);

		void setTerrain(std::unique_ptr<Terrains::Terrain> terrain);

	private:
		std::unique_ptr<Terrains::Terrain> m_terrain{};
		float m_lengthX{};
		float m_lengthZ{};
		float m_spacingX{};
		float m_spacingZ{};
	};
}
