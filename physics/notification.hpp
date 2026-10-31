#pragma once

#include "physics/simulationClock.hpp"
#include "physics/simulationStep.hpp"

#include <mutex>

namespace Physics
{
	class Notification
	{
	public:
		Notification(const SimulationClock& simulationClock);

		void forceGetNotification(SimulationStep& simulationStep);
		void getNotification(SimulationStep& simulationStep);
		void setNotification(const SimulationStep& simulationStep, bool isStateFrame);

	private:
		SimulationStep m_simulationStep{};
		const SimulationClock& m_simulationClock;
		bool m_unread{};
		bool m_ignoring = false;
		std::mutex m_mutex{};
	};
}
