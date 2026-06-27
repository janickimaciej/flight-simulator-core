#include "physics/timestep.hpp"

#include "common/config.hpp"

namespace Physics
{
	Timestep Timestep::previous() const
	{
		Timestep previousTimestep{};
		if (step == 0)
		{
			previousTimestep.step = Common::stepsPerSecond - 1;
			if (second == 0)
			{
				previousTimestep.second = secondsPerMinute - 1;
			}
			else
			{
				previousTimestep.second = second - 1;
			}
		}
		else
		{
			previousTimestep.second = second;
			previousTimestep.step = step - 1;
		}
		return previousTimestep;
	}

	Timestep Timestep::next() const
	{
		Timestep nextTimestep{};
		if (step == Common::stepsPerSecond - 1)
		{
			nextTimestep.step = 0;
			if (second == secondsPerMinute - 1)
			{
				nextTimestep.second = 0;
			}
			else
			{
				nextTimestep.second = second + 1;
			}
		}
		else
		{
			nextTimestep.second = second;
			nextTimestep.step = step + 1;
		}
		return nextTimestep;
	}

	Timestep operator-(const Timestep& timestep1, const Timestep& timestep2)
	{
		int second = static_cast<int>(timestep1.second) - static_cast<int>(timestep2.second);
		int step = static_cast<int>(timestep1.step) -
			static_cast<int>(timestep2.step);
		Timestep::normalize(second, step);
		return Timestep{static_cast<unsigned int>(second), static_cast<unsigned int>(step)};
	}

	Timestep operator+(const Timestep& timestep1, const Timestep& timestep2)
	{
		int second = static_cast<int>(timestep1.second) + static_cast<int>(timestep2.second);
		int step = static_cast<int>(timestep1.step) +
			static_cast<int>(timestep2.step);
		Timestep::normalize(second, step);
		return Timestep{static_cast<unsigned int>(second), static_cast<unsigned int>(step)};
	}

	bool operator==(const Timestep& timestep1, const Timestep& timestep2)
	{
		return timestep1.second == timestep2.second && timestep1.step == timestep2.step;
	}

	bool operator<(const Timestep& timestep1, const Timestep& timestep2)
	{
		return (timestep1 - timestep2).second >= 30;
	}

	bool operator<=(const Timestep& timestep1, const Timestep& timestep2)
	{
		return timestep1 < timestep2 || timestep1 == timestep2;
	}

	bool operator>(const Timestep& timestep1, const Timestep& timestep2)
	{
		return !(timestep1 <= timestep2);
	}

	void Timestep::normalize(int& second, int& step)
	{
		while (step < 0)
		{
			step += Common::stepsPerSecond;
			--second;
		}

		while (second < 0)
		{
			second += secondsPerMinute;
		}

		while (step >= Common::stepsPerSecond)
		{
			step -= Common::stepsPerSecond;
			++second;
		}

		while (second >= secondsPerMinute)
		{
			second -= secondsPerMinute;
		}
	}
}
