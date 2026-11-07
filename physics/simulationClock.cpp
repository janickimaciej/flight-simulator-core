#include "physics/simulationClock.hpp"

#include <chrono>

namespace Physics
{
	SimulationStep SimulationClock::getTime() const
	{
		Timestamp simulationNow = Timestamp::systemNow() - m_offset;
		return SimulationStep{simulationNow};
	}

	void SimulationClock::initializeOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		m_offset = calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp);
	}

	void SimulationClock::updateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		std::chrono::duration<float> difference = (calculateOffset(sendTimestamp, receiveTimestamp,
			serverTimestamp) - m_offset).getDuration();
		if (difference >= std::chrono::seconds{30})
		{
			difference -= std::chrono::minutes{1};
		}
		static constexpr float newOffsetWeight = 0.02f;
		m_offset = m_offset + Timestamp{newOffsetWeight * difference};
	}

	Timestamp SimulationClock::calculateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp) const
	{
		Timestamp latency{(receiveTimestamp - sendTimestamp).getDuration() / 2};
		return receiveTimestamp - (serverTimestamp + latency);
	}
}
