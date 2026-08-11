#include "common/frame.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Common
{
	State Frame::getState() const
	{
		return m_state;
	}

	void Frame::setState(const State& newState)
	{
		m_state = newState;
		updateMatrix();
	}

	void Frame::resetRotation()
	{
		m_state.orientation = glm::quat{1, 0, 0, 0};
		updateMatrix();
	}

	void Frame::rotate(const glm::vec3& axis, float angleRad)
	{
		glm::quat rotation = glm::angleAxis(angleRad, axis);
		m_state.orientation = rotation * m_state.orientation;
		m_state.normalize();
		updateMatrix();
	}

	void Frame::rotatePitch(float angleRad)
	{
		rotate(m_state.right(), angleRad);
	}

	void Frame::rotateYaw(float angleRad)
	{
		rotate(m_state.up(), -angleRad);
	}

	void Frame::rotateRoll(float angleRad)
	{
		rotate(m_state.direction(), -angleRad);
	}

	glm::vec3 Frame::getPos() const
	{
		return m_state.pos;
	}

	void Frame::setPos(const glm::vec3& pos)
	{
		if (pos == m_state.pos) return;
		m_state.pos = pos;
		updateMatrix();
	}

	Frame::Frame()
	{
		updateMatrix();
	}

	glm::mat4 Frame::getMatrix() const
	{
		return m_matrix;
	}

	float Frame::getScale() const
	{
		return m_scaleRatio;
	}

	void Frame::setScale(float scaleRatio)
	{
		if (scaleRatio == m_scaleRatio) return;
		m_scaleRatio = scaleRatio;
		updateMatrix();
	}

	void Frame::mirrorX()
	{
		m_mirrorX = !m_mirrorX;
		m_isWindingOrderClockwise = !m_isWindingOrderClockwise;
		updateMatrix();
	}

	void Frame::mirrorY()
	{
		m_mirrorY = !m_mirrorY;
		m_isWindingOrderClockwise = !m_isWindingOrderClockwise;
		updateMatrix();
	}

	void Frame::mirrorZ()
	{
		m_mirrorZ = !m_mirrorZ;
		m_isWindingOrderClockwise = !m_isWindingOrderClockwise;
		updateMatrix();
	}

	bool Frame::isWindingOrderClockwise() const
	{
		return m_isWindingOrderClockwise;
	}

	void Frame::updateMatrix()
	{
		glm::mat4 scaleMatrix = glm::scale(glm::mat4{1},
			glm::vec3
			{
				m_mirrorX ? -m_scaleRatio : m_scaleRatio,
				m_mirrorY ? -m_scaleRatio : m_scaleRatio,
				m_mirrorZ ? -m_scaleRatio : m_scaleRatio
			});
		m_matrix = m_state.matrix() * scaleMatrix;
	}
}
