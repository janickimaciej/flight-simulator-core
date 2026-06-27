#pragma once

#include "common/state.hpp"

#include <bitsery/traits/array.h>

#include <array>
#include <cstddef>

namespace App
{
	inline constexpr std::size_t stateFramePlayerInfoSerializedSize = 72;

	struct StateFramePlayerInfo
	{
		unsigned char playerId{};
		float pitch{};
		float yaw{};
		float roll{};
		float thrust{};
		bool trigger{};
		unsigned char airplaneType{};
		unsigned char hp{};
		std::array<float, Common::State::stateLength> state{};
	};

	template <typename T>
	void serialize(T& t, StateFramePlayerInfo& playerInfo)
	{
		t.value1b(playerInfo.playerId);
		t.value4b(playerInfo.pitch);
		t.value4b(playerInfo.yaw);
		t.value4b(playerInfo.roll);
		t.value4b(playerInfo.thrust);
		t.value1b(playerInfo.trigger);
		t.value1b(playerInfo.airplaneType);
		t.value1b(playerInfo.hp);
		t.container4b(playerInfo.state);
	}
}
