#pragma once

#include "common/airplaneCtrl.hpp"
#include "common/airplaneType.hpp"
#include "common/state.hpp"

namespace Common
{
	struct AirplaneInfo
	{
		State state{};
		AirplaneCtrl airplaneCtrl{};
		AirplaneType airplaneType{};
		int hp{};
	};
}
