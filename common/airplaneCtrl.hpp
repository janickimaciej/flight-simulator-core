#pragma once

namespace Common
{
	struct AirplaneCtrl
	{
		float elevatorAngleRad{};
		float rudderAngleRad{};
		float aileronsAngleRad{};
		float thrustRelative{};
		bool gunfire{};
	};
}
