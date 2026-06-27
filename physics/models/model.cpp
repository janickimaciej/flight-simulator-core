#include "physics/models/model.hpp"

#include "common/transformable.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	glm::mat4 Model::getModelMatrix() const
	{
		return getMatrix();
	}

	glm::vec3 Model::getPosition() const
	{
		return getState().position;
	}

	void Model::scale(float scaleRatio)
	{
		Common::Transformable::scale(scaleRatio);
	}
}
