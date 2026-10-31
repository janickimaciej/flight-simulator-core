#include "physics/simulationStep.hpp"

namespace Physics
{
	inline constexpr unsigned int secondsPerMinute = 60;

	SimulationStep operator-(const SimulationStep& simulationStep1,
		const SimulationStep& simulationStep2)
	{
		int second =
			static_cast<int>(simulationStep1.second) - static_cast<int>(simulationStep2.second);
		int step = static_cast<int>(simulationStep1.step) - static_cast<int>(simulationStep2.step);
		SimulationStep::normalize(second, step);
		return SimulationStep{static_cast<unsigned int>(second), static_cast<unsigned int>(step)};
	}

	SimulationStep operator+(const SimulationStep& simulationStep1,
		const SimulationStep& simulationStep2)
	{
		int second =
			static_cast<int>(simulationStep1.second) + static_cast<int>(simulationStep2.second);
		int step = static_cast<int>(simulationStep1.step) + static_cast<int>(simulationStep2.step);
		SimulationStep::normalize(second, step);
		return SimulationStep{static_cast<unsigned int>(second), static_cast<unsigned int>(step)};
	}

	bool operator==(const SimulationStep& simulationStep1, const SimulationStep& simulationStep2)
	{
		return simulationStep1.second == simulationStep2.second &&
			simulationStep1.step == simulationStep2.step;
	}

	bool operator<(const SimulationStep& simulationStep1, const SimulationStep& simulationStep2)
	{
		return (simulationStep1 - simulationStep2).second >= 30;
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
		SimulationStep prevSimulationStep{};
		if (step == 0)
		{
			prevSimulationStep.step = stepsPerSecond - 1;
			if (second == 0)
			{
				prevSimulationStep.second = secondsPerMinute - 1;
			}
			else
			{
				prevSimulationStep.second = second - 1;
			}
		}
		else
		{
			prevSimulationStep.second = second;
			prevSimulationStep.step = step - 1;
		}
		return prevSimulationStep;
	}

	SimulationStep SimulationStep::next() const
	{
		SimulationStep nextSimulationStep{};
		if (step == stepsPerSecond - 1)
		{
			nextSimulationStep.step = 0;
			if (second == secondsPerMinute - 1)
			{
				nextSimulationStep.second = 0;
			}
			else
			{
				nextSimulationStep.second = second + 1;
			}
		}
		else
		{
			nextSimulationStep.second = second;
			nextSimulationStep.step = step + 1;
		}
		return nextSimulationStep;
	}

	void SimulationStep::normalize(int& second, int& step)
	{
		while (step < 0)
		{
			step += stepsPerSecond;
			--second;
		}

		while (second < 0)
		{
			second += secondsPerMinute;
		}

		while (step >= stepsPerSecond)
		{
			step -= stepsPerSecond;
			++second;
		}

		while (second >= secondsPerMinute)
		{
			second -= secondsPerMinute;
		}
	}
}
