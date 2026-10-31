#pragma once

#include "common/state.hpp"
#include "physics/modelDynamics/bulletDynamics.hpp"
#include "physics/models/model.hpp"
#include "physics/simulationStep.hpp"

namespace Physics
{
	class Bullet : public Model
	{
	public:
		Bullet(const Common::State& state, const SimulationStep& spawnSimulationStep);
		Bullet(const Bullet& bullet) = default;
		Bullet(Bullet&& bullet) noexcept = default;
		virtual ~Bullet() = default;

		Bullet& operator=(const Bullet& bullet) = default;
		Bullet& operator=(Bullet&& bullet) = default;

		void update(const Bullet& prevBullet);
		const SimulationStep& getSpawnSimulationStep() const;

	private:
		BulletDynamics m_dynamics{};

		SimulationStep m_spawnSimulationStep{};
	};
}
