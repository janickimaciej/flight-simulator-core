#pragma once

#include "physics/simulationStep.hpp"
#include "physics/timestamp.hpp"

#include <atomic>

namespace Physics
{
	class SimulationClock
	{
	public:
		SimulationStep getTime() const;
		void initializeOffset(const Timestamp& sendTimestamp, const Timestamp& receiveTimestamp,
			const Timestamp& serverTimestamp);
		void updateOffset(const Timestamp& sendTimestamp, const Timestamp& receiveTimestamp,
			const Timestamp& serverTimestamp);

	private:
		std::atomic<Timestamp> m_offset{};

		Timestamp calculateOffset(const Timestamp& sendTimestamp, const Timestamp& receiveTimestamp,
			const Timestamp& serverTimestamp) const;
	};
}
