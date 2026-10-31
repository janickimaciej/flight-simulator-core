#include "physics/modelDynamics/bulletDynamics.hpp"

#include "physics/simulationStep.hpp"

#include <glm/glm.hpp>

namespace Physics
{
	Common::State BulletDynamics::computeNewState(const Common::State& oldState) const
	{
		Common::State newState{};

		static constexpr float g = 9.81f;
		glm::vec3 oldVelocityGlobal = oldState.orientation * oldState.velocity;
		newState.pos = oldState.pos + oldVelocityGlobal * SimulationStep::stepLength +
			glm::vec3{0, -g, 0} * SimulationStep::stepLength * SimulationStep::stepLength / 2.0f;
		glm::vec3 newVelocityGlobal =
			oldVelocityGlobal + glm::vec3{0, -g, 0} * SimulationStep::stepLength;
		newState.setOrientation(-glm::normalize(newVelocityGlobal));
		newState.velocity = glm::inverse(newState.orientation) * newVelocityGlobal;

		return newState;
	}
}
