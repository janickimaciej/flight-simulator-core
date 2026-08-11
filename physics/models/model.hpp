#pragma once

#include "common/transformable.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	class Model : public Common::Frame
	{
	public:
		virtual ~Model() = default;

		glm::mat4 getModelMatrix() const;
		glm::vec3 getPos() const;
		virtual void setScale(float scaleRatio) override; // local
	};
}
