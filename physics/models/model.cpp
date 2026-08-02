#include "physics/models/model.hpp"

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

	void Model::setScale(float scaleRatio)
	{
		Common::Transformable::setScale(scaleRatio);
	}
}
