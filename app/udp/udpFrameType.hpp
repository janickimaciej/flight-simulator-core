#pragma once

#include <cstdint>

namespace App
{
	enum class UDPFrameType
	{
		initReq,
		initRes,
		control,
		state
	};

	unsigned char toUChar(UDPFrameType udpFrameType);
	uint8_t toUInt8(UDPFrameType udpFrameType);
}
