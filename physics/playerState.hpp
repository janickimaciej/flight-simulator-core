#pragma once

#include "common/airplaneType.hpp"
#include "common/state.hpp"

namespace Physics
{
	struct PlayerState
	{
		Common::AirplaneType airplaneType;
		int hp{};
		Common::State state{};
	};
}
