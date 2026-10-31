#include "app/udp/udpSerializer.hpp"

#include "app/udp/frame/controlFrame.hpp"
#include "app/udp/frame/initReqFrame.hpp"
#include "app/udp/frame/initResFrame.hpp"
#include "physics/playerState.hpp"

#include <bitsery/adapter/buffer.h>
#include <bitsery/deserializer.h>
#include <bitsery/serializer.h>

#include <utility>

namespace App
{
	using OutputAdapter = bitsery::OutputBufferAdapter<std::vector<std::uint8_t>>;
	using InputAdapter = bitsery::InputBufferAdapter<std::vector<std::uint8_t>>;

	void UDPSerializer::serializeInitReqFrame(const Physics::Timestamp& clientTimestamp,
		Common::AirplaneType airplaneType, std::vector<std::uint8_t>& buffer)
	{
		InitReqFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.airplaneType = Common::toUChar(airplaneType);

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
		const Physics::Timestamp& serverTimestamp, const Physics::SimulationStep& simulationStep,
		int playerId, const Physics::PlayerInput& playerInput, std::vector<std::uint8_t>& buffer)
	{
		ControlFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.serverTimestamp = packTimestamp(serverTimestamp);
		frame.simulationStep = packSimulationStep(simulationStep);
		frame.playerId = static_cast<unsigned char>(playerId);
		frame.pitch = playerInput.pitch;
		frame.yaw = playerInput.yaw;
		frame.roll = playerInput.roll;
		frame.thrust = playerInput.thrust;
		frame.trigger = playerInput.trigger;

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::serializeStateFrame(const Physics::SimulationStep& simulationStep,
		const std::unordered_map<int, Physics::PlayerInfo>& playerInfos,
		std::vector<std::uint8_t>& buffer)
	{
		StateFrame frame{};
		frame.simulationStep = packSimulationStep(simulationStep);
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
					Common::toUChar(playerInfo.second.state.airplaneType),
					static_cast<unsigned char>(playerInfo.second.state.hp),
					playerInfo.second.state.state.toArray()
				});
		}

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::deserializeInitReqFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestamp& clientTimestamp, Common::AirplaneType& airplaneType)
	{
		InitReqFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		airplaneType = Common::fromUChar(frame.airplaneType);
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
		Physics::SimulationStep& simulationStep, int& playerId, Physics::PlayerInput& playerInput)
	{
		ControlFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		serverTimestamp = unpackTimestamp(frame.serverTimestamp);
		simulationStep = unpackSimulationStep(frame.simulationStep);
		playerId = frame.playerId;
		playerInput.pitch = frame.pitch;
		playerInput.yaw = frame.yaw;
		playerInput.roll = frame.roll;
		playerInput.thrust = frame.thrust;
		playerInput.trigger = frame.trigger;
	}

	void UDPSerializer::deserializeStateFrame(const std::vector<std::uint8_t>& buffer,
		Physics::SimulationStep& simulationStep,
		std::unordered_map<int, Physics::PlayerInfo>& playerInfos)
	{
		StateFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		simulationStep = unpackSimulationStep(frame.simulationStep);
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
						static_cast<Common::AirplaneType>(playerInfo.airplaneType),
						playerInfo.hp,
						Common::State(playerInfo.state)
					}
				}});
		}
	}

	std::array<unsigned char, 2> UDPSerializer::packTimestamp(const Physics::Timestamp& timestamp)
	{
		std::array<unsigned char, 2> serializedTimestamp{};
		serializedTimestamp[0] = static_cast<unsigned char>(timestamp.getSecond());
		serializedTimestamp[0] <<= 2;
		serializedTimestamp[0] |= static_cast<unsigned char>(timestamp.getMillisecond() >> 8);
		serializedTimestamp[1] = static_cast<unsigned char>(timestamp.getMillisecond());
		return serializedTimestamp;
	}

	std::array<unsigned char, 2> UDPSerializer::packSimulationStep(
		const Physics::SimulationStep& simulationStep)
	{
		std::array<unsigned char, 2> serializedSimulationStep{};
		serializedSimulationStep[0] = static_cast<unsigned char>(simulationStep.second);
		serializedSimulationStep[0] <<= 2;
		serializedSimulationStep[0] |= static_cast<unsigned char>(simulationStep.step >> 8);
		serializedSimulationStep[1] = static_cast<unsigned char>(simulationStep.step);
		return serializedSimulationStep;
	}

	Physics::Timestamp UDPSerializer::unpackTimestamp(const std::array<unsigned char, 2>& timestamp)
	{
		unsigned int second = static_cast<unsigned int>(timestamp[0] >> 2);
		unsigned int millisecond =
			static_cast<unsigned int>(timestamp[0] - ((timestamp[0] >> 2) << 2));
		millisecond <<= 8;
		millisecond |= static_cast<unsigned int>(timestamp[1]);
		return Physics::Timestamp{second, millisecond};
	}

	Physics::SimulationStep UDPSerializer::unpackSimulationStep(
		const std::array<unsigned char, 2>& simulationStep)
	{
		Physics::SimulationStep deserializedSimulationStep{};
		deserializedSimulationStep.second = static_cast<unsigned int>(simulationStep[0] >> 2);
		deserializedSimulationStep.step =
			static_cast<unsigned int>(simulationStep[0] - ((simulationStep[0] >> 2) << 2));
		deserializedSimulationStep.step <<= 8;
		deserializedSimulationStep.step |= static_cast<unsigned int>(simulationStep[1]);
		return deserializedSimulationStep;
	}
}
