#include "physics/models/bullet.hpp"

namespace Physics
{
	Bullet::Bullet(const Common::State& state, const Timestep& spawnTimestep) :
		m_spawnTimestep{spawnTimestep}
	{
		setState(state);
	}
	
	void Bullet::update(const Bullet& previousBullet)
	{
		setState(m_dynamics.computeNewState(previousBullet.getState()));
	}

	const Timestep& Bullet::getSpawnTimestep() const
	{
		return m_spawnTimestep;
	}
}
