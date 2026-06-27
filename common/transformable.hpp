#pragma once

#include "state.hpp"

#include <glm/glm.hpp>

namespace Common
{
	class Transformable
	{
	public:
		virtual State getState() const;
		virtual void setState(const State& newState);

		virtual void rotate(const glm::vec3& axis, float angleRad); // locally
		virtual void resetRotation(); // locally
		virtual void translate(const glm::vec3& translation);

		virtual void rotatePitch(float angleRad); // locally
		virtual void rotateYaw(float angleRad); // locally
		virtual void rotateRoll(float angleRad); // locally
		virtual void moveZ(float distance); // locally

		virtual ~Transformable() = default;
	
	protected:
		Transformable();
		glm::mat4 getMatrix() const;
		virtual void scale(float scaleRatio); // locally
		virtual void mirrorX(); // locally
		virtual void mirrorY(); // locally
		virtual void mirrorZ(); // locally
		bool isWindingOrderClockwise() const;

	private:
		State m_state{};
		bool m_mirrorX = false;
		bool m_mirrorY = false;
		bool m_mirrorZ = false;
		bool m_isWindingOrderClockwise = false;
		float m_scaleRatio = 1;
		glm::mat4 m_matrix{};

		void updateMatrix();
	};
}
