#include "physics/simulationClock.hpp"

#include "common/config.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <chrono>

namespace Physics
{
	Timestep SimulationClock::getTime() const
	{
		Timestamp offset = m_offset.load();
		std::chrono::duration<float> simulationTime =
			std::chrono::steady_clock::now().time_since_epoch() -
			std::chrono::seconds(offset.second) - std::chrono::milliseconds(offset.millisecond);

		std::chrono::minutes minutes =
			std::chrono::duration_cast<std::chrono::minutes>(simulationTime);
		std::chrono::seconds seconds =
			std::chrono::duration_cast<std::chrono::seconds>(simulationTime - minutes);
		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds>(simulationTime - minutes -
				seconds);

		static constexpr float stepsPerMillisecond = static_cast<float>(Common::stepsPerSecond) /
			millisecondsPerSecond;
		return Timestep
			{
				static_cast<unsigned int>(seconds.count()),
				static_cast<unsigned int>(milliseconds.count() * stepsPerMillisecond)
			};
	}

	void SimulationClock::initializeOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		m_offset.store(calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp));
	}

	void SimulationClock::updateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		static constexpr float newOffsetWeight = 0.02f;
		Timestamp difference =
			calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp) - m_offset;
		int differenceMillisecond =
			static_cast<int>(difference.second * millisecondsPerSecond + difference.millisecond);
		if (difference.second >= secondsPerMinute / 2)
		{
			differenceMillisecond -= secondsPerMinute * millisecondsPerSecond;
		}
		differenceMillisecond = static_cast<int>(differenceMillisecond * newOffsetWeight);
		int differenceSecond = differenceMillisecond / static_cast<int>(millisecondsPerSecond);
		differenceMillisecond -= differenceSecond * static_cast<int>(millisecondsPerSecond);

		int offsetSecond = static_cast<int>(m_offset.load().second) + differenceSecond;
		int offsetMillisecond =
			static_cast<int>(m_offset.load().millisecond) + differenceMillisecond;

		Timestamp::normalize(offsetSecond, offsetMillisecond);

		m_offset = Timestamp{static_cast<unsigned int>(offsetSecond),
			static_cast<unsigned int>(offsetMillisecond)};
	}

	Timestamp SimulationClock::calculateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp) const
	{
		Timestamp latency = (receiveTimestamp - sendTimestamp) / 2;
		return receiveTimestamp - (serverTimestamp + latency);
	}
}
