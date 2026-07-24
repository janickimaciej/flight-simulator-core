#include "app/udp/udpFrameType.hpp"

namespace App
{
	unsigned char toUChar(UDPFrameType udpFrameType)
	{
		return static_cast<unsigned char>(udpFrameType);
	}

	std::uint8_t toUInt8(UDPFrameType udpFrameType)
	{
		return static_cast<std::uint8_t>(udpFrameType);
	}
}
