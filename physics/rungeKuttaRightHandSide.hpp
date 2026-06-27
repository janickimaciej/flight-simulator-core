#pragma once

#include <array>
#include <cstddef>

namespace Physics
{
	template <std::size_t stateLength>
	class RungeKuttaRightHandSide
	{
	public:
		virtual void rightHandSide(float time, const std::array<float, stateLength>& state,
			std::array<float, stateLength>& stateDerivative) const = 0;
		virtual ~RungeKuttaRightHandSide() = default;
	};
}
