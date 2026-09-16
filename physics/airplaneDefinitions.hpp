#pragma once

#include "common/airplaneType.hpp"
#include "common/airplaneCentersOfMass.hpp"
#include "physics/airplaneDefinition.hpp"
#include "physics/airplaneParamsDatabase/jw1.hpp"
#include "physics/airplaneParamsDatabase/mustang.hpp"
#include "physics/collisions/ellipsoid.hpp"

#include <array>

namespace Physics
{
	inline const std::array<AirplaneDefinition, Common::airplaneTypeCount> airplaneDefinitions
	{
		AirplaneDefinition
		{
			mustangParams,
			glm::vec3{0, 0, -100},
			-Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::mustang)],
			glm::vec3{0, 0, -500},
			Collisions::Airplane
			{
				Collisions::Ellipsoid
				{
					glm::vec3{0, -0.18f, 4.91f} - Common::airplaneCentersOfMass[
						Common::toSizeT(Common::AirplaneType::mustang)],
					5.48f,
					0.96f,
					4.9f
				},
				std::array<glm::vec3, 6>
				{
					-Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::mustang)],
					glm::vec3{0, 0.08f, 9.84f} - Common::airplaneCentersOfMass[
						Common::toSizeT(Common::AirplaneType::mustang)],
					glm::vec3{5.49f, -0.15f, 3.64f} - Common::airplaneCentersOfMass[
						Common::toSizeT(Common::AirplaneType::mustang)],
					glm::vec3{-5.49f, -0.15f, 3.64f} - Common::airplaneCentersOfMass[
						Common::toSizeT(Common::AirplaneType::mustang)],
					glm::vec3{0, -2.1f, 2.78f} - Common::airplaneCentersOfMass[
						Common::toSizeT(Common::AirplaneType::mustang)],
					glm::vec3{0, 1.61f, 9.07f} - Common::airplaneCentersOfMass[
						Common::toSizeT(Common::AirplaneType::mustang)]
				}
			},
			100
		},
		AirplaneDefinition
		{
			jw1Params,
			glm::vec3{0, 0, -343},
			-Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)] +
				glm::vec3{0.6f, 0.63f, 3.14f},
			glm::vec3{0, 0, -1000},
			Collisions::Airplane
			{
				Collisions::Ellipsoid
				{
					glm::vec3{0, 0.39f, 10.07f} -
						Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)],
					6.63f,
					1.58f,
					10.02f
				},
				std::array<glm::vec3, 6>
				{
					-Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)],
					glm::vec3{0, 0, 19.98f} -
						Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)],
					glm::vec3{6.5f, 0.45f, 14.2f} -
						Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)],
					glm::vec3{-6.5f, 0.45f, 14.2f} -
						Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)],
					glm::vec3{0, -0.69f, 17.04f} -
						Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)],
					glm::vec3{0, 2.58f, 19.39f} -
						Common::airplaneCentersOfMass[Common::toSizeT(Common::AirplaneType::jw1)]
				}
			},
			100
		}
	};
}
