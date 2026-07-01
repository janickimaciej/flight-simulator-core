#include "physics/collisions/collisionTest.hpp"

#include "common/state.hpp"
#include "common/terrains/terrain.hpp"
#include "physics/collisions/airplane.hpp"
#include "physics/collisions/ellipsoid.hpp"

#include <glm/glm.hpp>

namespace Physics::Collisions
{
	bool CollisionTest::collides(const glm::vec3& moving, const Common::State& movingPrevState,
			const Common::State& movingNextState, const Common::Terrains::Terrain& stationary)
	{
		glm::vec3 segmentStart{movingPrevState.matrix() * glm::vec4(moving, 1)};
		glm::vec3 segmentEnd{movingNextState.matrix() * glm::vec4(moving, 1)};
		return (segmentStart).y <= stationary.height(segmentStart.x, segmentEnd.z) ||
			(segmentEnd).y <= stationary.height(segmentEnd.x, segmentEnd.z);
	}

	bool CollisionTest::collides(const glm::vec3& moving, const Common::State& movingPrevState,
		const Common::State& movingNextState, const Airplane& stationary,
		const Common::State& stationaryState)
	{
		return collides(moving, movingPrevState, movingNextState, stationary.ellipsoid,
			stationaryState);
	}

	bool CollisionTest::collides(const glm::vec3& moving, const Common::State& movingPrevState,
		const Common::State& movingNextState, const Ellipsoid& stationary,
		const Common::State& stationaryState)
	{
		glm::vec3 segmentStart = toEllipsoidSystem(moving, movingPrevState, stationary,
			stationaryState);
		glm::vec3 segmentEnd = toEllipsoidSystem(moving, movingNextState, stationary,
			stationaryState);
		glm::vec3 segment = segmentEnd - segmentStart;

		float a = glm::dot(segment, segment);
		float b = glm::dot(segmentStart, segment);
		float c = glm::dot(segmentStart, segmentStart) - 1;

		if (c <= 0)
		{
			return true;
		}
		else if (b > 0)
		{
			return false;
		}
		else if (b * b - a * c < 0)
		{
			return false;
		}
		else if (a + 2 * b + c <= 0)
		{
			return true;
		}
		else if (a + b > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CollisionTest::collides(const Airplane& moving, const Common::State& movingPrevState,
		const Common::State& movingNextState, const Common::Terrains::Terrain& stationary)
	{
		for (const glm::vec3& point : moving.points)
		{
			if (collides(point, movingPrevState, movingNextState, stationary))
			{
				return true;
			}
		}
		return false;
	}

	bool CollisionTest::collides(const Airplane& moving, const Common::State& movingPrevState,
		const Common::State& movingNextState, const Airplane& stationary,
		const Common::State& stationaryState)
	{
		for (const glm::vec3& point : moving.points)
		{
			if (collides(point, movingPrevState, movingNextState, stationary, stationaryState))
			{
				return true;
			}
		}
		return false;
	}

	glm::vec3 CollisionTest::toEllipsoidSystem(const glm::vec3& point,
		const Common::State& pointState, const Ellipsoid& ellipsoid,
		const Common::State& ellipsoidState)
	{
		glm::vec3 transformedPoint = glm::vec3{glm::inverse(ellipsoidState.matrix()) *
			pointState.matrix() * glm::vec4(point, 1)} - ellipsoid.center;
		transformedPoint.x /= ellipsoid.semiaxisX;
		transformedPoint.y /= ellipsoid.semiaxisY;
		transformedPoint.z /= ellipsoid.semiaxisZ;
		return transformedPoint;
	}
}
