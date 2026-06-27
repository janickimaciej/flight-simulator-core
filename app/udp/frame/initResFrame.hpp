#pragma once

#include "app/udp/udpFrameType.hpp"

#include <bitsery/traits/array.h>

#include <array>

namespace App
{
	struct InitResFrame
	{
		unsigned char frameType = toUChar(UDPFrameType::initRes);
		std::array<unsigned char, 2> clientTimestamp{};
		std::array<unsigned char, 2> serverTimestamp{};
		unsigned char playerId{};
	};

	template <typename T>
	void serialize(T& t, InitResFrame& frame)
	{
		t.value1b(frame.frameType);
		t.container1b(frame.clientTimestamp);
		t.container1b(frame.serverTimestamp);
		t.value1b(frame.playerId);
	}
}
