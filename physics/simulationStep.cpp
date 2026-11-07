#include "physics/simulationStep.hpp"

#include <cmath>

namespace Physics
{
	SimulationStep::SimulationStep(unsigned int second, unsigned int step) :
		SimulationStep{static_cast<int>(second), static_cast<int>(step)}
	{ }

	SimulationStep::SimulationStep(int second, int step)
	{
		normalize(second, step);

		m_second = static_cast<unsigned int>(second);
		m_step = static_cast<unsigned int>(step);
	}

	SimulationStep::SimulationStep(const Timestamp& timestamp)
	{
		m_second = timestamp.getSecond();
		static constexpr float millisecondsPerSecond = 1000.0f;
		static constexpr float stepsPerMillisecond = stepsPerSecond / millisecondsPerSecond;
		m_step = static_cast<unsigned int>(
			std::floor(timestamp.getMillisecond() * stepsPerMillisecond));
	}

	unsigned int SimulationStep::getSecond() const
	{
		return m_second;
	}

	unsigned int SimulationStep::getStep() const
	{
		return m_step;
	}

	SimulationStep operator-(const SimulationStep& simulationStep1,
		const SimulationStep& simulationStep2)
	{
		int second = static_cast<int>(simulationStep1.m_second) -
			static_cast<int>(simulationStep2.m_second);
		int step = static_cast<int>(simulationStep1.m_step) -
			static_cast<int>(simulationStep2.m_step);
		SimulationStep::normalize(second, step);
		return SimulationStep{static_cast<unsigned int>(second), static_cast<unsigned int>(step)};
	}

	SimulationStep operator+(const SimulationStep& simulationStep1,
		const SimulationStep& simulationStep2)
	{
		int second = static_cast<int>(simulationStep1.m_second) +
			static_cast<int>(simulationStep2.m_second);
		int step = static_cast<int>(simulationStep1.m_step) +
			static_cast<int>(simulationStep2.m_step);
		SimulationStep::normalize(second, step);
		return SimulationStep{static_cast<unsigned int>(second), static_cast<unsigned int>(step)};
	}

	bool operator==(const SimulationStep& simulationStep1, const SimulationStep& simulationStep2)
	{
		return simulationStep1.m_second == simulationStep2.m_second &&
			simulationStep1.m_step == simulationStep2.m_step;
	}

	bool operator<(const SimulationStep& simulationStep1, const SimulationStep& simulationStep2)
	{
		static constexpr unsigned int secondsPerMinute = 60;
		return (simulationStep1 - simulationStep2).m_second >= secondsPerMinute / 2;
	}

	bool operator<=(const SimulationStep& simulationStep1, const SimulationStep& simulationStep2)
	{
		return simulationStep1 < simulationStep2 || simulationStep1 == simulationStep2;
	}

	bool operator>(const SimulationStep& simulationStep1, const SimulationStep& simulationStep2)
	{
		return !(simulationStep1 <= simulationStep2);
	}

	SimulationStep SimulationStep::prev() const
	{
		int second = static_cast<int>(m_second);
		int step = static_cast<int>(m_step) - 1;
		normalize(second, step);
		return SimulationStep{second, step};
	}

	SimulationStep SimulationStep::next() const
	{
		int second = static_cast<int>(m_second);
		int step = static_cast<int>(m_step) + 1;
		normalize(second, step);
		return SimulationStep{second, step};
	}

	void SimulationStep::normalize(int& second, int& step)
	{
		int fullSecondsInStep =
			static_cast<int>(std::floor(step / static_cast<float>(stepsPerSecond)));
		step = static_cast<int>(step - fullSecondsInStep * stepsPerSecond);
		second += fullSecondsInStep;

		static constexpr float secondsPerMinute = 60.0f;
		int fullMinutesInSecond = static_cast<int>(std::floor(second / secondsPerMinute));
		second = static_cast<int>(second - fullMinutesInSecond * secondsPerMinute);
	}
}
