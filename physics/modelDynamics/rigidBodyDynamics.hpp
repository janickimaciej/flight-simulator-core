#pragma once

#include "common/state.hpp"
#include "physics/rungeKuttaRightHandSide.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Physics
{
	class RigidBodyDynamics : public RungeKuttaRightHandSide<Common::State::stateLength>
	{
	public:
		virtual void rightHandSide(float,
			const std::array<float, Common::State::stateLength>& state,
			std::array<float, Common::State::stateLength>& stateDerivative) const override;
		Common::State computeNewState(const Common::State& oldState) const;
		virtual ~RigidBodyDynamics() = default;

	protected:
		RigidBodyDynamics(float mass, const glm::mat3& momentOfInertia);

	private:
		float m_mass{};
		glm::mat3 m_momentOfInertia{};
		glm::mat3 m_momentOfInertiaInverse{};

		virtual void computeNetForceAndNetTorque(const Common::State& state, glm::vec3& netForce,
			glm::vec3& netTorque) const = 0;
	};
}
