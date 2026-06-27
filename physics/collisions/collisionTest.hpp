#pragma once

#include "common/state.hpp"
#include "common/terrains/terrain.hpp"
#include "physics/collisions/airplane.hpp"
#include "physics/collisions/ellipsoid.hpp"

#include <glm/glm.hpp>

namespace Physics::Collisions
{
	class CollisionTest
	{
	public:
		static bool collides(const glm::vec3& moving, const Common::State& movingPreviousState,
			const Common::State& movingNextState, const Common::Terrains::Terrain& stationary);
		static bool collides(const glm::vec3& moving, const Common::State& movingPreviousState,
			const Common::State& movingNextState, const Airplane& stationary,
			const Common::State& stationaryState);
		static bool collides(const glm::vec3& moving, const Common::State& movingPreviousState,
			const Common::State& movingNextState, const Ellipsoid& stationary,
			const Common::State& stationaryState);
		static bool collides(const Airplane& moving, const Common::State& movingPreviousState,
			const Common::State& movingNextState, const Common::Terrains::Terrain& stationary);
		static bool collides(const Airplane& moving, const Common::State& movingPreviousState,
			const Common::State& movingNextState, const Airplane& stationary,
			const Common::State& stationaryState);

	private:
		static glm::vec3 toEllipsoidSystem(const glm::vec3& point, const Common::State& pointState,
			const Ellipsoid& ellipsoid, const Common::State& ellipsoidState);
	};
}
