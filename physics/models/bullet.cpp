#include "physics/models/bullet.hpp"

namespace Physics
{
	Bullet::Bullet(const Common::State& state, const Timestep& spawnTimestep) :
		m_spawnTimestep{spawnTimestep}
	{
		setState(state);
	}

	void Bullet::update(const Bullet& prevBullet)
	{
		setState(m_dynamics.computeNewState(prevBullet.getState()));
	}

	const Timestep& Bullet::getSpawnTimestep() const
	{
		return m_spawnTimestep;
	}
}
