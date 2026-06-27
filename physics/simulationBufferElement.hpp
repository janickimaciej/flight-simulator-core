#pragma once

#include "common/mapName.hpp"
#include "physics/scene.hpp"
#include "physics/simulationBufferPlayer.hpp"

#include <array>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace Physics
{
	struct SimulationBufferElement
	{
		Scene scene;
		mutable std::mutex mutex{};
		std::unordered_map<int, SimulationBufferPlayer> players{};
		bool lock{};
		std::array<std::vector<int>, 2> removedPlayers{};

		SimulationBufferElement(Common::MapName mapName);
	};
}
