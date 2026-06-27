#pragma once

#include "physics/playerInput.hpp"
#include "physics/playerState.hpp"

namespace Physics
{
	struct PlayerInfo
	{
		PlayerInput input{};
		PlayerState state{};
	};
}
