#include "physics/notification.hpp"

#include "common/config.hpp"

namespace Physics
{
	Notification::Notification(const SimulationClock& simulationClock) :
		m_simulationClock{simulationClock}
	{ }

	void Notification::forceGetNotification(Timestep& timestep)
	{
		std::scoped_lock lock{m_mutex};

		timestep = m_timestep;
		m_unread = false;
	}

	void Notification::getNotification(Timestep& timestep)
	{
		static constexpr Timestep beginIngoringOffset{0,
			static_cast<unsigned int>(Common::stepsPerSecond * 0.9f)};
		static constexpr Timestep endIgnoringOffset{0,
			static_cast<unsigned int>(Common::stepsPerSecond * 0.2f)};
		if (timestep <= m_simulationClock.getTime() - beginIngoringOffset)
		{
			m_ignoring = true;
		}
		if (timestep > m_simulationClock.getTime() - endIgnoringOffset)
		{
			m_ignoring = false;
		}

		{
			std::scoped_lock lock{m_mutex};

			if (!m_ignoring && m_unread && m_timestep < timestep)
			{
				timestep = m_timestep;
			}
			m_unread = false;
		}
	}

	void Notification::setNotification(const Timestep& timestep, bool isStateFrame)
	{
		std::scoped_lock lock{m_mutex};

		if (isStateFrame || !m_unread || timestep < m_timestep)
		{
			m_timestep = timestep;
			m_unread = true;
		}
	}
}
