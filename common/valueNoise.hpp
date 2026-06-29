#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <random>

namespace Common
{
	template <unsigned int periodExponent>
	class ValueNoise
	{
	public:
		ValueNoise(unsigned int seed);
		float height(float x, float z) const;
		float heightDerivX(float x, float z) const;
		float heightDerivZ(float x, float z) const;

	private:
		static constexpr std::size_t period = 1 << periodExponent;
		std::array<float, period> m_values{};
		std::array<unsigned int, period> m_permutation{};

		void common(float x, float z, float& tX, float& tZ, float& y00, float& y01, float& y10,
			float& y11) const;
		static float smoothstep(float t);
		static float smoothstepDeriv(float t);
		static float lerp(float valueStart, float valueEnd, float t);
	};

	template <unsigned int periodExponent>
	ValueNoise<periodExponent>::ValueNoise(unsigned int seed)
	{
		std::mt19937 generator(seed);

		std::uniform_real_distribution<float> floatDistribution(0, 1);
		for (std::size_t i = 0; i < period; ++i)
		{
			m_values[i] = floatDistribution(generator);
			m_permutation[i] = static_cast<unsigned int>(i);
		}

		std::uniform_int_distribution<unsigned int> intDistribution(0, period - 1);
		for (std::size_t i = 0; i < period; ++i)
		{
			unsigned int index = intDistribution(generator);
			std::swap(m_permutation[i], m_permutation[index]);
		}
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::height(float x, float z) const
	{
		float tX{};
		float tZ{};
		float y00{};
		float y01{};
		float y10{};
		float y11{};
		common(x, z, tX, tZ, y00, y01, y10, y11);

		float smoothTX = smoothstep(tX);
		float smoothTZ = smoothstep(tZ);

		float lerp0 = lerp(y00, y10, smoothTX);
		float lerp1 = lerp(y01, y11, smoothTX);

		return lerp(lerp0, lerp1, smoothTZ);
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::heightDerivX(float x, float z) const
	{
		float tX{};
		float tZ{};
		float y00{};
		float y01{};
		float y10{};
		float y11{};
		common(x, z, tX, tZ, y00, y01, y10, y11);

		float smoothDerivTX = smoothstepDeriv(tX);
		float smoothTZ = smoothstep(tZ);

		return smoothDerivTX * lerp(y10 - y00, y11 - y01, smoothTZ);
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::heightDerivZ(float x, float z) const
	{
		float tX{};
		float tZ{};
		float y00{};
		float y01{};
		float y10{};
		float y11{};
		common(x, z, tX, tZ, y00, y01, y10, y11);

		float smoothTX = smoothstep(tX);
		float smoothDerivTZ = smoothstepDeriv(tZ);

		float lerp0 = lerp(y00, y10, smoothTX);
		float lerp1 = lerp(y01, y11, smoothTX);

		return smoothDerivTZ * (lerp1 - lerp0);
	}

	template <unsigned int periodExponent>
	void ValueNoise<periodExponent>::common(float x, float z, float& tX, float& tZ, float& y00,
		float& y01, float& y10, float& y11) const
	{
		int xInt = static_cast<int>(std::floor(x));
		int zInt = static_cast<int>(std::floor(z));

		tX = x - xInt;
		tZ = z - zInt;

		unsigned int periodMask = period - 1;
		unsigned int x0 = xInt & periodMask;
		unsigned int x1 = (x0 + 1) & periodMask;
		unsigned int z0 = zInt & periodMask;
		unsigned int z1 = (z0 + 1) & periodMask;

		y00 = m_values[m_permutation[(m_permutation[x0] + z0) & periodMask]];
		y01 = m_values[m_permutation[(m_permutation[x0] + z1) & periodMask]];
		y10 = m_values[m_permutation[(m_permutation[x1] + z0) & periodMask]];
		y11 = m_values[m_permutation[(m_permutation[x1] + z1) & periodMask]];
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::smoothstep(float t)
	{
		return ((6 * t - 15) * t + 10) * t * t * t;
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::smoothstepDeriv(float t)
	{
		return ((30 * t - 60) * t + 30) * t * t;
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::lerp(float valueStart, float valueEnd, float t)
	{
		return (1 - t) * valueStart + t * valueEnd;
	}
}
