#pragma once

#include "physics/simulationClock.hpp"
#include "physics/timestep.hpp"

#include <mutex>

namespace Physics
{
	class Notification
	{
	public:
		Notification(const SimulationClock& simulationClock);
		void forceGetNotification(Timestep& timestep);
		void getNotification(Timestep& timestep);
		void setNotification(const Timestep& timestep, bool isStateFrame);

	private:
		Timestep m_timestep{};
		const SimulationClock& m_simulationClock;
		bool m_unread{};
		bool m_ignoring = false;
		std::mutex m_mutex{};
	};
}
