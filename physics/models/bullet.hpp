#pragma once

#include "common/state.hpp"
#include "physics/modelDynamics/bulletDynamics.hpp"
#include "physics/models/model.hpp"
#include "physics/timestep.hpp"

namespace Physics
{
	class Bullet : public Model
	{
	public:
		Bullet(const Common::State& state, const Timestep& spawnTimestep);
		Bullet(const Bullet& bullet) = default;
		Bullet(Bullet&& bullet) noexcept = default;
		Bullet& operator=(const Bullet& bullet) = default;
		Bullet& operator=(Bullet&& bullet) = default;
		void update(const Bullet& previousBullet);
		const Timestep& getSpawnTimestep() const;
		virtual ~Bullet() = default;

	private:
		BulletDynamics m_dynamics{};

		Timestep m_spawnTimestep{};
	};
}
