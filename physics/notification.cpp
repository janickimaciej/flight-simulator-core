#include "physics/notification.hpp"

namespace Physics
{
	Notification::Notification(const SimulationClock& simulationClock) :
		m_simulationClock{simulationClock}
	{ }

	void Notification::forceGetNotification(SimulationStep& simulationStep)
	{
		std::scoped_lock lock{m_mutex};

		simulationStep = m_simulationStep;
		m_unread = false;
	}

	void Notification::getNotification(SimulationStep& simulationStep)
	{
		static const SimulationStep beginIgnoringOffset{0u,
			static_cast<unsigned int>(SimulationStep::stepsPerSecond * 0.9f)};
		static const SimulationStep endIgnoringOffset{0u,
			static_cast<unsigned int>(SimulationStep::stepsPerSecond * 0.2f)};
		if (simulationStep <= m_simulationClock.getTime() - beginIgnoringOffset)
		{
			m_ignoring = true;
		}
		if (simulationStep > m_simulationClock.getTime() - endIgnoringOffset)
		{
			m_ignoring = false;
		}

		{
			std::scoped_lock lock{m_mutex};

			if (!m_ignoring && m_unread && m_simulationStep < simulationStep)
			{
				simulationStep = m_simulationStep;
			}
			m_unread = false;
		}
	}

	void Notification::setNotification(const SimulationStep& simulationStep, bool isStateFrame)
	{
		std::scoped_lock lock{m_mutex};

		if (isStateFrame || !m_unread || simulationStep < m_simulationStep)
		{
			m_simulationStep = simulationStep;
			m_unread = true;
		}
	}
}
