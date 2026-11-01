#pragma once

#include <chrono>

namespace Physics
{
	class Timestamp
	{
	public:
		Timestamp() = default;
		Timestamp(unsigned int second, unsigned int millisecond);
		Timestamp(int second, int millisecond);
		Timestamp(const std::chrono::duration<float>& duration);

		unsigned int getSecond() const;
		unsigned int getMillisecond() const;
		std::chrono::duration<float> getDuration() const;

		friend Timestamp operator+(const Timestamp& timestamp1, const Timestamp& timestamp2);
		friend Timestamp operator-(const Timestamp& timestamp1, const Timestamp& timestamp2);

		static Timestamp systemNow();

	private:
		unsigned int m_second{};
		unsigned int m_millisecond{};


		static void normalize(int& second, int& millisecond);
	};
}
