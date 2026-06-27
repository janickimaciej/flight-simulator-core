#pragma once

#include <chrono>
#include <functional>

namespace Physics
{
	struct Timestamp
	{
		unsigned int second{};
		unsigned int millisecond{};

		Timestamp() = default;
		Timestamp(unsigned int second, unsigned int millisecond);
		Timestamp(std::chrono::duration<float> timestamp);

		static Timestamp systemNow();

		friend Timestamp operator+(const Timestamp& timestamp1, const Timestamp& timestamp2);
		friend Timestamp operator-(const Timestamp& timestamp1, const Timestamp& timestamp2);
		friend Timestamp operator*(float number, const Timestamp& timestamp);
		friend Timestamp operator/(const Timestamp& timestamp, float number);

		static void normalize(int& second, int& millisecond);
	};
}
