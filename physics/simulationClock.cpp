#include "physics/simulationClock.hpp"

#include <chrono>

namespace Physics
{
	inline constexpr unsigned int millisecondsPerSecond = 1000;

	SimulationStep SimulationClock::getTime() const
	{
		Timestamp simulationNow = Timestamp::systemNow() - m_offset;
		static constexpr float stepsPerMillisecond =
			static_cast<float>(SimulationStep::stepsPerSecond) / millisecondsPerSecond;
		return SimulationStep
			{
				simulationNow.getSecond(),
				static_cast<unsigned int>(simulationNow.getMillisecond() * stepsPerMillisecond)
			};
	}

	void SimulationClock::initializeOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		m_offset = calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp);
	}

	void SimulationClock::updateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		static constexpr float newOffsetWeight = 0.02f;
		Timestamp difference =
			calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp) - m_offset;
		int differenceMillisecond =
			static_cast<int>(difference.getSecond() * millisecondsPerSecond +
				difference.getMillisecond());
		static constexpr unsigned int secondsPerMinute = 60;
		if (difference.getSecond() >= secondsPerMinute / 2)
		{
			differenceMillisecond -= secondsPerMinute * millisecondsPerSecond;
		}
		differenceMillisecond = static_cast<int>(differenceMillisecond * newOffsetWeight);
		int differenceSecond = differenceMillisecond / static_cast<int>(millisecondsPerSecond);
		differenceMillisecond -= differenceSecond * static_cast<int>(millisecondsPerSecond);

		Timestamp offset = m_offset;
		int offsetSecond = static_cast<int>(offset.getSecond()) + differenceSecond;
		int offsetMillisecond =
			static_cast<int>(offset.getMillisecond()) + differenceMillisecond;

		m_offset = Timestamp{offsetSecond, offsetMillisecond};
	}

	Timestamp SimulationClock::calculateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp) const
	{
		Timestamp latency = (receiveTimestamp - sendTimestamp) / 2;
		return receiveTimestamp - (serverTimestamp + latency);
	}
}
