#include "physics/modelDynamics/rigidBodyDynamics.hpp"

#include "common/state.hpp"
#include "physics/rungeKutta.hpp"
#include "physics/simulationClock.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <array>

namespace Physics
{
	RigidBodyDynamics::RigidBodyDynamics(float mass, const glm::mat3& momentOfInertia) :
		m_mass{mass},
		m_momentOfInertia{momentOfInertia},
		m_momentOfInertiaInverse{glm::inverse(momentOfInertia)}
	{ }

	void RigidBodyDynamics::rightHandSide(float,
		const std::array<float, Common::State::stateLength>& state,
		std::array<float, Common::State::stateLength>& stateDerivative) const
	{
		Common::State stateObj{state};
		Common::State stateDerivativeObj{};

		glm::vec3 netForce{};
		glm::vec3 netTorque{};
		computeNetForceAndNetTorque(stateObj, netForce, netTorque);

		stateDerivativeObj.position = stateObj.orientation * stateObj.velocity;

		stateDerivativeObj.orientation = stateObj.orientation *
			glm::quat{0, stateObj.angVelocityRad} / 2.0f;

		stateDerivativeObj.velocity = netForce / m_mass - glm::cross(stateObj.angVelocityRad,
			stateObj.velocity);

		stateDerivativeObj.angVelocityRad = m_momentOfInertiaInverse * (netTorque -
			glm::cross(stateObj.angVelocityRad, m_momentOfInertia * stateObj.angVelocityRad));

		stateDerivativeObj.toArray(stateDerivative);
	}

	Common::State RigidBodyDynamics::computeNewState(const Common::State& oldState) const
	{
		std::array<float, Common::State::stateLength> oldStateArr{};
		oldState.toArray(oldStateArr);

		std::array<float, Common::State::stateLength> newStateArr{};
		RungeKutta<Common::State::stateLength>::RK4(0, physicsTimeStep, oldStateArr, *this,
			newStateArr);

		Common::State newState{newStateArr};
		newState.normalize();

		return newState;
	}
}
