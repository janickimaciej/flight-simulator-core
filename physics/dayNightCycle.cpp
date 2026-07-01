#include "physics/dayNightCycle.hpp"

#include "physics/simulationClock.hpp"

namespace Physics
{
	void DayNightCycle::updateTime(const DayNightCycle& prevDayNightCycle)
	{
		static constexpr float secondsPerDay = 5 * 24;
		m_timeOfDay = prevDayNightCycle.getTimeOfDay() + physicsTimeStep / secondsPerDay;
		m_day = prevDayNightCycle.getDay();
		while (m_timeOfDay >= 1)
		{
			m_timeOfDay -= 1;
			++m_day;
		}
	}

	int DayNightCycle::getDay() const
	{
		return m_day;
	}

	float DayNightCycle::getTimeOfDay() const
	{
		return m_timeOfDay;
	}
}
