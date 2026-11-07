#include "physics/timestamp.hpp"

#include <cmath>

namespace Physics
{
	Timestamp::Timestamp(unsigned int second, unsigned int millisecond) :
		Timestamp{static_cast<int>(second), static_cast<int>(millisecond)}
	{ }

	Timestamp::Timestamp(int second, int millisecond)
	{
		normalize(second, millisecond);

		m_second = static_cast<unsigned int>(second);
		m_millisecond = static_cast<unsigned int>(millisecond);
	}

	Timestamp::Timestamp(const std::chrono::duration<float>& duration)
	{
		std::chrono::minutes minutes = std::chrono::floor<std::chrono::minutes>(duration);
		std::chrono::milliseconds milliseconds =
			std::chrono::round<std::chrono::milliseconds>(duration - minutes);

		int second = 0;
		int millisecond = static_cast<int>(milliseconds.count());
		normalize(second, millisecond);

		m_second = static_cast<unsigned int>(second);
		m_millisecond = static_cast<unsigned int>(millisecond);
	}

	unsigned int Timestamp::getSecond() const
	{
		return m_second;
	}

	unsigned int Timestamp::getMillisecond() const
	{
		return m_millisecond;
	}

	std::chrono::duration<float> Timestamp::getDuration() const
	{
		return std::chrono::seconds{m_second} + std::chrono::milliseconds{m_millisecond};
	}

	Timestamp operator+(const Timestamp& timestamp1, const Timestamp& timestamp2)
	{
		return Timestamp{timestamp1.getDuration() + timestamp2.getDuration()};
	}

	Timestamp operator-(const Timestamp& timestamp1, const Timestamp& timestamp2)
	{
		return Timestamp{timestamp1.getDuration() - timestamp2.getDuration()};
	}

	Timestamp Timestamp::systemNow()
	{
		return Timestamp{std::chrono::steady_clock::now().time_since_epoch()};
	}

	void Timestamp::normalize(int& second, int& millisecond)
	{
		static constexpr float millisecondsPerSecond = 1000.0f;
		int fullSecondsInMillisecond =
			static_cast<int>(std::floor(millisecond / millisecondsPerSecond));
		millisecond =
			static_cast<int>(millisecond - fullSecondsInMillisecond * millisecondsPerSecond);
		second += fullSecondsInMillisecond;

		static constexpr float secondsPerMinute = 60.0f;
		int fullMinutesInSecond = static_cast<int>(std::floor(second / secondsPerMinute));
		second = static_cast<int>(second - fullMinutesInSecond * secondsPerMinute);
	}
}
