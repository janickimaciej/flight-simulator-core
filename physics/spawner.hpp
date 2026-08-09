#pragma once

#include "common/airplaneType.hpp"
#include "common/state.hpp"

#include <ctime>
#include <random>

namespace Physics
{
	class Spawner
	{
	public:
		Common::State spawn(Common::AirplaneType airplaneType);

	private:
		std::mt19937 m_generator{static_cast<unsigned int>(std::time(nullptr))};
	};
}
