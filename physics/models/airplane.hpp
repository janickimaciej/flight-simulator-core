#pragma once

#include "common/airplaneInfo.hpp"
#include "common/airplaneType.hpp"
#include "physics/airplaneParams/airplaneParams.hpp"
#include "physics/collisions/airplane.hpp"
#include "physics/flightCtrl.hpp"
#include "physics/modelDynamics/airplaneDynamics.hpp"
#include "physics/models/model.hpp"
#include "physics/playerInfo.hpp"
#include "physics/timestep.hpp"

#include <memory>
#include <optional>

namespace Physics
{
	class Airplane : public Model
	{
	public:
		Airplane(const Common::AirplaneType& airplaneType, int hp);
		Airplane(const Airplane& airplane);
		Airplane(Airplane&& airplane) noexcept;
		void updatePhase1(const Airplane* prevAirplane, const PlayerInfo& playerInfo,
			bool isStateLocked);
		void updatePhase2();
		PlayerInfo getPlayerInfo() const;
		Common::AirplaneInfo getAirplaneInfo() const;
		Common::AirplaneType getAirplaneType() const;
		const Common::AirplaneCtrl& getCtrl() const;
		const Collisions::Airplane& getCollisionModel() const;
		const std::optional<Timestep>& getLastShotTimestep() const;
		void setLastShotTimestep(const std::optional<Timestep>& lastShotTimestep);
		void damage(int hp);
		void destroy();
		void heal(int hp);
		virtual ~Airplane() = default;

	private:
		Common::AirplaneType m_airplaneType;
		const AirplaneParams& m_airplaneParams;
		FlightCtrl m_flightCtrl;
		AirplaneDynamics m_dynamics;
		Collisions::Airplane m_collisionModel{};
		std::optional<Timestep> m_lastShotTimestep = std::nullopt;
		int m_hp{};
	};
}
