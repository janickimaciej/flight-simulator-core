#include "app/udp/udpFrameType.hpp"

#include <cstdint>

namespace App
{
	unsigned char toUChar(UDPFrameType udpFrameType)
	{
		return static_cast<unsigned char>(udpFrameType);
	}

	uint8_t toUInt8(UDPFrameType udpFrameType)
	{
		return static_cast<uint8_t>(udpFrameType);
	}
}
