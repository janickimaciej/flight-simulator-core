#pragma once

namespace Physics
{
	struct SimulationStep
	{
		static constexpr unsigned int stepsPerSecond = 100;
		static constexpr float stepLength = 1.0f / stepsPerSecond;

		unsigned int second{};
		unsigned int step{};

		friend SimulationStep operator-(const SimulationStep& simulationStep1,
			const SimulationStep& simulationStep2);
		friend SimulationStep operator+(const SimulationStep& simulationStep1,
			const SimulationStep& simulationStep2);

		friend bool operator==(const SimulationStep& simulationStep1,
			const SimulationStep& simulationStep2);
		friend bool operator<(const SimulationStep& simulationStep1,
			const SimulationStep& simulationStep2);
		friend bool operator<=(const SimulationStep& simulationStep1,
			const SimulationStep& simulationStep2);
		friend bool operator>(const SimulationStep& simulationStep1,
			const SimulationStep& simulationStep2);

		SimulationStep prev() const;
		SimulationStep next() const;

	private:
		static void normalize(int& second, int& step);
	};
}
