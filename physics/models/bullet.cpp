#include "physics/models/bullet.hpp"

namespace Physics
{
	Bullet::Bullet(const Common::State& state, const SimulationStep& spawnSimulationStep) :
		m_spawnSimulationStep{spawnSimulationStep}
	{
		setState(state);
	}

	void Bullet::update(const Bullet& prevBullet)
	{
		setState(m_dynamics.computeNewState(prevBullet.getState()));
	}

	const SimulationStep& Bullet::getSpawnSimulationStep() const
	{
		return m_spawnSimulationStep;
	}
}
