#include "physics/timestamp.hpp"

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
		std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
		std::chrono::seconds seconds =
			std::chrono::duration_cast<std::chrono::seconds>(duration - minutes);
		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds>(duration - minutes - seconds);

		int second = static_cast<int>(seconds.count());
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
		static constexpr unsigned int millisecondsPerSecond = 1000;
		static constexpr unsigned int secondsPerMinute = 60;

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
