#pragma once

#include "common/airplaneCtrl.hpp"
#include "common/airplaneTypeName.hpp"
#include "common/state.hpp"

namespace Common
{
	struct AirplaneInfo
	{
		State state{};
		AirplaneCtrl airplaneCtrl{};
		AirplaneTypeName airplaneTypeName{};
		int hp{};
	};
}
