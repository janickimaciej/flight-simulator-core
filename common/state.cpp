#include "common/state.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Common
{
	State::State(const std::array<float, stateLength>& arr)
	{
		position.x = arr[0];
		position.y = arr[1];
		position.z = arr[2];
		orientation.w = arr[3];
		orientation.x = arr[4];
		orientation.y = arr[5];
		orientation.z = arr[6];
		velocity.x = arr[7];
		velocity.y = arr[8];
		velocity.z = arr[9];
		angVelocityRad.x = arr[10];
		angVelocityRad.y = arr[11];
		angVelocityRad.z = arr[12];
	}

	void State::toArray(std::array<float, stateLength>& array) const
	{
		array[0] = position.x;
		array[1] = position.y;
		array[2] = position.z;
		array[3] = orientation.w;
		array[4] = orientation.x;
		array[5] = orientation.y;
		array[6] = orientation.z;
		array[7] = velocity.x;
		array[8] = velocity.y;
		array[9] = velocity.z;
		array[10] = angVelocityRad.x;
		array[11] = angVelocityRad.y;
		array[12] = angVelocityRad.z;
	}

	std::array<float, State::stateLength> State::toArray() const
	{
		std::array<float, stateLength> array{};
		toArray(array);
		return array;
	}

	glm::mat4 State::matrix() const
	{
		glm::mat4 orientationMatrix = glm::mat4_cast(orientation);
		glm::mat4 positionMatrix = glm::translate(glm::mat4{1}, position);
		return positionMatrix * orientationMatrix;
	}

	glm::vec3 State::right() const
	{
		return orientation * glm::vec3{1, 0, 0};
	}

	glm::vec3 State::up() const
	{
		return orientation * glm::vec3{0, 1, 0};
	}

	glm::vec3 State::direction() const
	{
		return orientation * glm::vec3{0, 0, 1};
	}

	void State::setOrientation(const glm::vec3& direction)
	{
		glm::vec3 right = glm::normalize(glm::cross
		(
			glm::vec3{0, 1, 0},
			glm::vec3{direction}
		));

		glm::vec3 up = glm::normalize(glm::cross
		(
			glm::vec3{direction},
			glm::vec3{right}
		));

		glm::mat3 orientationMatrix =
		{
			right.x, right.y, right.z,
			up.x, up.y, up.z,
			direction.x, direction.y, direction.z
		};

		orientation = glm::quat_cast(orientationMatrix);
	}

	void State::normalize()
	{
		orientation = glm::normalize(orientation);
	}
}
