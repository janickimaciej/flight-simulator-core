#pragma once

#include "app/udp/udpFrameType.hpp"

#include <bitsery/traits/array.h>

#include <array>

namespace App
{
	struct InitReqFrame
	{
		unsigned char frameType = toUChar(UDPFrameType::initReq);
		std::array<unsigned char, 2> clientTimestamp{};
		unsigned char airplaneType{};
	};

	template <typename T>
	void serialize(T& t, InitReqFrame& frame)
	{
		t.value1b(frame.frameType);
		t.container1b(frame.clientTimestamp);
		t.value1b(frame.airplaneType);
	}
}
