#include "physics/models/model.hpp"

#include "common/transformable.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	glm::mat4 Model::getModelMatrix() const
	{
		return getMatrix();
	}

	glm::vec3 Model::getPos() const
	{
		return getState().pos;
	}

	void Model::scale(float scaleRatio)
	{
		Common::Transformable::scale(scaleRatio);
	}
}
