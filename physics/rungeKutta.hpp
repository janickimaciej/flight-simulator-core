#pragma once

#include "physics/rungeKuttaRightHandSide.hpp"

#include <array>
#include <cstddef>

namespace Physics
{
	template <std::size_t stateLength>
	class RungeKutta
	{
	public:
		RungeKutta() = delete;
		static void RK4(float oldTime, float deltaTime,
			const std::array<float, stateLength>& oldState,
			const RungeKuttaRightHandSide<stateLength>& rightHandSide,
			std::array<float, stateLength>& newState);
		~RungeKutta() = delete;
	};

	template <std::size_t stateLength>
	void RungeKutta<stateLength>::RK4(float oldTime, float timeStep,
		const std::array<float, stateLength>& oldState,
		const RungeKuttaRightHandSide<stateLength>& rightHandSide,
		std::array<float, stateLength>& newState)
	{
		std::array<std::array<float, stateLength>, 4> k{};

		float time{};
		std::array<float, stateLength> state{};
	
		rightHandSide.rightHandSide(oldTime, oldState, k[0]);

		time = oldTime + timeStep / 2;
		for (std::size_t i = 0; i < stateLength; ++i)
		{
			state[i] = oldState[i] + timeStep / 2 * k[0][i];
		}
		rightHandSide.rightHandSide(time, state, k[1]);

		time = oldTime + timeStep / 2;
		for (std::size_t i = 0; i < stateLength; ++i)
		{
			state[i] = oldState[i] + timeStep / 2 * k[1][i];
		}
		rightHandSide.rightHandSide(time, state, k[2]);

		time = oldTime + timeStep;
		for (std::size_t i = 0; i < stateLength; ++i)
		{
			state[i] = oldState[i] + timeStep * k[2][i];
		}
		rightHandSide.rightHandSide(time, state, k[3]);

		for (std::size_t i = 0; i < stateLength; ++i)
		{
			newState[i] = oldState[i] + timeStep / 6 * (k[0][i] + 2 * k[1][i] + 2 * k[2][i] +
				k[3][i]);
		}
	}
}
