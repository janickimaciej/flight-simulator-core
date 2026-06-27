#pragma once

#include "app/udp/frame/stateFrame.hpp"
#include "common/airplaneTypeName.hpp"
#include "common/config.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace App
{
	inline constexpr std::size_t maxFrameSize = emptyStateFrameSerializedSize +
		Common::maxPlayerCount * stateFramePlayerInfoSerializedSize;

	class UDPSerializer
	{
	public:
		static void serializeInitReqFrame(const Physics::Timestamp& clientTimestamp,
			Common::AirplaneTypeName airplaneTypeName, std::vector<std::uint8_t>& buffer);
		static void serializeInitResFrame(const Physics::Timestamp& clientTimestamp,
			const Physics::Timestamp& serverTimestamp, int playerId,
			std::vector<std::uint8_t>& buffer);
		static void serializeControlFrame(const Physics::Timestamp& clientTimestamp,
			const Physics::Timestamp& serverTimestamp, const Physics::Timestep& timestep,
			int playerId, const Physics::PlayerInput& playerInput,
			std::vector<std::uint8_t>& buffer);
		static void serializeStateFrame(const Physics::Timestep& timestep,
			const std::unordered_map<int, Physics::PlayerInfo>& playerInfos,
			std::vector<std::uint8_t>& buffer);
		
		static void deserializeInitReqFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Common::AirplaneTypeName& airplaneTypeName);
		static void deserializeInitResFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
			int& playerId);
		static void deserializeControlFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
			Physics::Timestep& timestep, int& playerId, Physics::PlayerInput& playerInput);
		static void deserializeStateFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestep& timestep, std::unordered_map<int, Physics::PlayerInfo>& playerInfos);

	private:
		static std::array<unsigned char, 2> packTimestamp(const Physics::Timestamp& timestamp);
		static std::array<unsigned char, 2> packTimestep(const Physics::Timestep& timestep);

		static Physics::Timestamp unpackTimestamp(const std::array<unsigned char, 2>& timestamp);
		static Physics::Timestep unpackTimestep(const std::array<unsigned char, 2>& timestep);
	};
}
