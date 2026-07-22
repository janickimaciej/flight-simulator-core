#pragma once

#include "common/config.hpp"

namespace Physics
{
	inline constexpr unsigned int millisecondsPerSecond = 1000;
	inline constexpr unsigned int secondsPerMinute = 60;

	struct Timestep
	{
		unsigned int second{};
		unsigned int step{};

		friend Timestep operator-(const Timestep& timestep1, const Timestep& timestep2);
		friend Timestep operator+(const Timestep& timestep1, const Timestep& timestep2);

		friend bool operator==(const Timestep& timestep1, const Timestep& timestep2);
		friend bool operator<(const Timestep& timestep1, const Timestep& timestep2);
		friend bool operator<=(const Timestep& timestep1, const Timestep& timestep2);
		friend bool operator>(const Timestep& timestep1, const Timestep& timestep2);

		Timestep prev() const;
		Timestep next() const;

	private:
		static void normalize(int& second, int& step);
	};
}
