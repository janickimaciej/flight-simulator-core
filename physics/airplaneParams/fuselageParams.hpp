#pragma once

#include <glm/glm.hpp>

namespace Physics
{
	struct FuselageParams
	{
		float frontArea{};
		float frontDragCoef{};
		glm::vec3 frontDragPoint{};

		float sideArea{};
		float sideDragCoef{};
		glm::vec3 sideDragPoint{};
	};
}
