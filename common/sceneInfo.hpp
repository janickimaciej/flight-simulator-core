#pragma once

#include "common/airplaneInfo.hpp"
#include "common/bulletInfo.hpp"

#include <unordered_map>
#include <vector>

namespace Common
{
	struct SceneInfo
	{
		std::unordered_map<int, AirplaneInfo> airplaneInfos{};
		std::vector<BulletInfo> bulletInfos{};
		int day{};
		float timeOfDay{};
	};
}
