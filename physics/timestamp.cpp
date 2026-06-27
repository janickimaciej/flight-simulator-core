#include "physics/timestamp.hpp"

#include "physics/timestep.hpp"

#include <chrono>

namespace Physics
{
	Timestamp::Timestamp(unsigned int second, unsigned int millisecond) :
		second{second},
		millisecond{millisecond}
	{ }

	Timestamp::Timestamp(std::chrono::duration<float> timestamp)
	{
		std::chrono::minutes minutes =
			std::chrono::duration_cast<std::chrono::minutes>(timestamp);
		std::chrono::seconds seconds =
			std::chrono::duration_cast<std::chrono::seconds>(timestamp - minutes);
		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds>(timestamp - minutes -
				seconds);

		second = static_cast<unsigned int>(seconds.count());
		millisecond = static_cast<unsigned int>(milliseconds.count());
	}

	Timestamp Timestamp::systemNow()
	{
		return Timestamp{std::chrono::steady_clock::now().time_since_epoch()};
	}

	Timestamp operator+(const Timestamp& timestamp1, const Timestamp& timestamp2)
	{
		int second = static_cast<int>(timestamp1.second) + static_cast<int>(timestamp2.second);
		int millisecond = static_cast<int>(timestamp1.millisecond) +
			static_cast<int>(timestamp2.millisecond);
		Timestamp::normalize(second, millisecond);
		return Timestamp{static_cast<unsigned int>(second), static_cast<unsigned int>(millisecond)};
	}

	Timestamp operator-(const Timestamp& timestamp1, const Timestamp& timestamp2)
	{
		int second = static_cast<int>(timestamp1.second) - static_cast<int>(timestamp2.second);
		int millisecond = static_cast<int>(timestamp1.millisecond) -
			static_cast<int>(timestamp2.millisecond);
		Timestamp::normalize(second, millisecond);
		return Timestamp{static_cast<unsigned int>(second), static_cast<unsigned int>(millisecond)};
	}

	Timestamp operator*(float number, const Timestamp& timestamp)
	{
		int second = static_cast<int>(static_cast<int>(timestamp.second) * number + 0.5f);
		int millisecond = static_cast<int>(static_cast<int>(timestamp.millisecond) * number + 0.5f);
		Timestamp::normalize(second, millisecond);
		return Timestamp{static_cast<unsigned int>(second), static_cast<unsigned int>(millisecond)};
	}

	Timestamp operator/(const Timestamp& timestamp, float number)
	{
		int second = static_cast<int>(static_cast<int>(timestamp.second) / number + 0.5f);
		int millisecond = static_cast<int>(static_cast<int>(timestamp.millisecond) / number + 0.5f);
		Timestamp::normalize(second, millisecond);
		return Timestamp{static_cast<unsigned int>(second), static_cast<unsigned int>(millisecond)};
	}

	void Timestamp::normalize(int& second, int& millisecond)
	{
		while (millisecond < 0)
		{
			millisecond += millisecondsPerSecond;
			--second;
		}

		while (second < 0)
		{
			second += secondsPerMinute;
		}

		while (millisecond >= millisecondsPerSecond)
		{
			millisecond -= millisecondsPerSecond;
			++second;
		}

		while (second >= secondsPerMinute)
		{
			second -= secondsPerMinute;
		}
	}
}
