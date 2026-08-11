#pragma once

#include "state.hpp"

#include <glm/glm.hpp>

namespace Common
{
	class Frame
	{
	public:
		virtual ~Frame() = default;

		State getState() const;
		void setState(const State& newState);

		void resetRotation(); // local
		void rotate(const glm::vec3& axis, float angleRad); // local
		void rotatePitch(float angleRad); // local
		void rotateYaw(float angleRad); // local
		void rotateRoll(float angleRad); // local

		glm::vec3 getPos() const;
		void setPos(const glm::vec3& pos);

	protected:
		Frame();

		glm::mat4 getMatrix() const;
		float getScale() const; // local
		virtual void setScale(float scaleRatio); // local
		virtual void mirrorX(); // local
		virtual void mirrorY(); // local
		virtual void mirrorZ(); // local
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
