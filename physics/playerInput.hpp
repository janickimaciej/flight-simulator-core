#pragma once

namespace Physics
{
	struct PlayerInput
	{
		float pitch{};
		float yaw{};
		float roll{};
		float thrust{};
		bool trigger{};
	};
}
