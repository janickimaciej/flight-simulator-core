#pragma once

#include "physics/timestamp.hpp"

namespace Physics
{
	struct SimulationStep
	{
		static constexpr unsigned int stepsPerSecond = 100;
		static constexpr float stepLength = 1.0f / stepsPerSecond;

		SimulationStep() = default;
		SimulationStep(unsigned int second, unsigned int step);
		SimulationStep(int second, int step);
		SimulationStep(const Timestamp& timestamp);

		unsigned int getSecond() const;
		unsigned int getStep() const;

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
		unsigned int m_second{};
		unsigned int m_step{};

		static void normalize(int& second, int& step);
	};
}
