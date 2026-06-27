#pragma once

namespace Physics
{
	class DayNightCycle
	{
	public:
		void updateTime(const DayNightCycle& previousDayNightCycle);
	
		int getDay() const;
		float getTimeOfDay() const;

	private:
		int m_day{};
		float m_timeOfDay{};
	};
}
