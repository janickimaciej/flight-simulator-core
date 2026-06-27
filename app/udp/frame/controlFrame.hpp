#pragma once

#include "app/udp/udpFrameType.hpp"

#include <bitsery/traits/array.h>

#include <array>

namespace App
{
	struct ControlFrame
	{
		unsigned char frameType = toUChar(UDPFrameType::control);
		std::array<unsigned char, 2> clientTimestamp{};
		std::array<unsigned char, 2> serverTimestamp{};
		std::array<unsigned char, 2> timestep{};
		unsigned char playerId{};
		float pitch{};
		float yaw{};
		float roll{};
		float thrust{};
		bool trigger{};
	};

	template <typename T>
	void serialize(T& t, ControlFrame& frame)
	{
		t.value1b(frame.frameType);
		t.container1b(frame.clientTimestamp);
		t.container1b(frame.serverTimestamp);
		t.container1b(frame.timestep);
		t.value1b(frame.playerId);
		t.value4b(frame.pitch);
		t.value4b(frame.yaw);
		t.value4b(frame.roll);
		t.value4b(frame.thrust);
		t.value1b(frame.trigger);
	}
}
