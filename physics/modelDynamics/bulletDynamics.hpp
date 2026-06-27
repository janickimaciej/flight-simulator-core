#pragma once

#include "common/state.hpp"

namespace Physics
{
	class BulletDynamics
	{
	public:
		Common::State computeNewState(const Common::State& oldState) const;
	};
}
