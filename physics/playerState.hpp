#pragma once

#include "common/airplaneTypeName.hpp"
#include "common/state.hpp"

namespace Physics
{
	struct PlayerState
	{
		Common::AirplaneTypeName airplaneTypeName;
		int hp{};
		Common::State state{};
	};
}
