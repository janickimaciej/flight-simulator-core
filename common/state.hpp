#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <array>
#include <cstddef>

namespace Common
{
	struct State
	{
		static constexpr std::size_t stateLength = 13;

		glm::vec3 pos{0, 0, 0};
		glm::quat orientation{1, 0, 0, 0};
		glm::vec3 velocity{0, 0, 0}; // in local coordinates
		glm::vec3 angVelocityRad{0, 0, 0}; // in local coordinates

		State() = default;
		State(const std::array<float, stateLength>& arr);

		void toArray(std::array<float, stateLength>& array) const;
		std::array<float, State::stateLength> toArray() const;
		glm::mat4 matrix() const;
		glm::vec3 right() const;
		glm::vec3 up() const;
		glm::vec3 direction() const;
		void setOrientation(const glm::vec3& direction); // direction must be a unit vector
		void normalize();
	};
}
