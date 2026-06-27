#include "app/udp/udpSerializer.hpp"

#include "app/udp/frame/controlFrame.hpp"
#include "app/udp/frame/initReqFrame.hpp"
#include "app/udp/frame/initResFrame.hpp"
#include "app/udp/frame/stateFrame.hpp"
#include "app/udp/udpFrameType.hpp"
#include "common/airplaneTypeName.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
#include "physics/playerState.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace App
{
	using OutputAdapter = bitsery::OutputBufferAdapter<std::vector<std::uint8_t>>;
	using InputAdapter = bitsery::InputBufferAdapter<std::vector<std::uint8_t>>;

	void UDPSerializer::serializeInitReqFrame(const Physics::Timestamp& clientTimestamp,
		Common::AirplaneTypeName airplaneTypeName, std::vector<std::uint8_t>& buffer)
	{
		InitReqFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.airplaneType = toUChar(airplaneTypeName);

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::serializeInitResFrame(const Physics::Timestamp& clientTimestamp,
		const Physics::Timestamp& serverTimestamp, int playerId,
		std::vector<std::uint8_t>& buffer)
	{
		InitResFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.serverTimestamp = packTimestamp(serverTimestamp);
		frame.playerId = static_cast<unsigned char>(playerId);

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::serializeControlFrame(const Physics::Timestamp& clientTimestamp,
		const Physics::Timestamp& serverTimestamp, const Physics::Timestep& timestep, int playerId,
		const Physics::PlayerInput& playerInput, std::vector<std::uint8_t>& buffer)
	{
		ControlFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.serverTimestamp = packTimestamp(serverTimestamp);
		frame.timestep = packTimestep(timestep);
		frame.playerId = static_cast<unsigned char>(playerId);
		frame.pitch = playerInput.pitch;
		frame.yaw = playerInput.yaw;
		frame.roll = playerInput.roll;
		frame.thrust = playerInput.thrust;
		frame.trigger = playerInput.trigger;

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::serializeStateFrame(const Physics::Timestep& timestep,
		const std::unordered_map<int, Physics::PlayerInfo>& playerInfos,
		std::vector<std::uint8_t>& buffer)
	{
		StateFrame frame{};
		frame.timestep = packTimestep(timestep);
		for (const std::pair<const int, Physics::PlayerInfo>& playerInfo : playerInfos)
		{
			frame.playerInfos.push_back(
				StateFramePlayerInfo
				{
					static_cast<unsigned char>(playerInfo.first),
					playerInfo.second.input.pitch,
					playerInfo.second.input.yaw,
					playerInfo.second.input.roll,
					playerInfo.second.input.thrust,
					playerInfo.second.input.trigger,
					toUChar(playerInfo.second.state.airplaneTypeName),
					static_cast<unsigned char>(playerInfo.second.state.hp),
					playerInfo.second.state.state.toArray()
				});
		}

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::deserializeInitReqFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestamp& clientTimestamp, Common::AirplaneTypeName& airplaneTypeName)
	{
		InitReqFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		airplaneTypeName = Common::fromUChar(frame.airplaneType);
	}

	void UDPSerializer::deserializeInitResFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp, int& playerId)
	{
		InitResFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		serverTimestamp = unpackTimestamp(frame.serverTimestamp);
		playerId = frame.playerId;
	}

	void UDPSerializer::deserializeControlFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
		Physics::Timestep& timestep, int& playerId, Physics::PlayerInput& playerInput)
	{
		ControlFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		serverTimestamp = unpackTimestamp(frame.serverTimestamp);
		timestep = unpackTimestep(frame.timestep);
		playerId = frame.playerId;
		playerInput.pitch = frame.pitch;
		playerInput.yaw = frame.yaw;
		playerInput.roll = frame.roll;
		playerInput.thrust = frame.thrust;
		playerInput.trigger = frame.trigger;
	}

	void UDPSerializer::deserializeStateFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestep& timestep, std::unordered_map<int, Physics::PlayerInfo>& playerInfos)
	{
		StateFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		timestep = unpackTimestep(frame.timestep);
		for (const StateFramePlayerInfo& playerInfo : frame.playerInfos)
		{
			playerInfos.insert({playerInfo.playerId,
				Physics::PlayerInfo
				{
					Physics::PlayerInput
					{
						playerInfo.pitch,
						playerInfo.yaw,
						playerInfo.roll,
						playerInfo.thrust,
						playerInfo.trigger
					},
					Physics::PlayerState
					{
						static_cast<Common::AirplaneTypeName>(playerInfo.airplaneType),
						playerInfo.hp,
						Common::State(playerInfo.state)
					}
				}});
		}
	}
	
	std::array<unsigned char, 2> UDPSerializer::packTimestamp(const Physics::Timestamp& timestamp)
	{
		std::array<unsigned char, 2> serializedTimestamp{};
		serializedTimestamp[0] = static_cast<unsigned char>(timestamp.second);
		serializedTimestamp[0] <<= 2;
		serializedTimestamp[0] |= static_cast<unsigned char>(timestamp.millisecond >> 8);
		serializedTimestamp[1] = static_cast<unsigned char>(timestamp.millisecond);
		return serializedTimestamp;
	}

	std::array<unsigned char, 2> UDPSerializer::packTimestep(const Physics::Timestep& timestep)
	{
		std::array<unsigned char, 2> serializedTimestep{};
		serializedTimestep[0] = static_cast<unsigned char>(timestep.second);
		serializedTimestep[0] <<= 2;
		serializedTimestep[0] |= static_cast<unsigned char>(timestep.step >> 8);
		serializedTimestep[1] = static_cast<unsigned char>(timestep.step);
		return serializedTimestep;
	}

	Physics::Timestamp UDPSerializer::unpackTimestamp(const std::array<unsigned char, 2>& timestamp)
	{
		Physics::Timestamp deserializedTimestamp{};
		deserializedTimestamp.second = static_cast<unsigned int>(timestamp[0] >> 2);
		deserializedTimestamp.millisecond =
			static_cast<unsigned int>(timestamp[0] - ((timestamp[0] >> 2) << 2));
		deserializedTimestamp.millisecond <<= 8;
		deserializedTimestamp.millisecond |= static_cast<unsigned int>(timestamp[1]);
		return deserializedTimestamp;
	}

	Physics::Timestep UDPSerializer::unpackTimestep(const std::array<unsigned char, 2>& timestep)
	{
		Physics::Timestep deserializedTimestep{};
		deserializedTimestep.second = static_cast<unsigned int>(timestep[0] >> 2);
		deserializedTimestep.step =
			static_cast<unsigned int>(timestep[0] - ((timestep[0] >> 2) << 2));
		deserializedTimestep.step <<= 8;
		deserializedTimestep.step |= static_cast<unsigned int>(timestep[1]);
		return deserializedTimestep;
	}
}
