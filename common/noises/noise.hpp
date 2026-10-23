#pragma once

#include <algorithm>
#include <array>
#include <random>
#include <cmath>
#include <cstddef>

namespace Common
{
	template <unsigned int periodExponent>
	class Noise
	{
	public:
		Noise(unsigned int seed);
		virtual ~Noise() = default;

		virtual float height(float x, float z) const = 0;
		virtual float heightDerivX(float x, float z) const = 0;
		virtual float heightDerivZ(float x, float z) const = 0;

	protected:
		static constexpr std::size_t m_period = 1 << periodExponent;
		static constexpr unsigned int m_periodMask = m_period - 1;
		std::array<std::size_t, 2 * m_period> m_permutation{};

		void common(float x, float z, float& tX, float& tZ, std::size_t& index00,
			std::size_t& index01, std::size_t& index10, std::size_t& index11) const;
		static float smoothstep(float t);
		static float smoothstepDeriv(float t);
		static float lerp(float valueStart, float valueEnd, float t);

	private:
		std::size_t hash(unsigned int x, unsigned int z) const;
	};

	template <unsigned int periodExponent>
	Noise<periodExponent>::Noise(unsigned int seed)
	{
		std::mt19937 generator{seed};
		std::uniform_int_distribution<unsigned int> intDistribution{0, m_period - 1};

		for (std::size_t i = 0; i < m_period; ++i)
		{
			m_permutation[i] = static_cast<unsigned int>(i);
		}

		for (std::size_t i = 0; i < m_period; ++i)
		{
			unsigned int index = intDistribution(generator);
			std::swap(m_permutation[i], m_permutation[index]);
		}

		for (std::size_t i = 0; i < m_period; ++i)
		{
			m_permutation[m_period + i] = m_permutation[i];
		}
	}

	template <unsigned int periodExponent>
	void Noise<periodExponent>::common(float x, float z, float& tX, float& tZ,
		std::size_t& index00, std::size_t& index01, std::size_t& index10,
		std::size_t& index11) const
	{
		int xFloor = static_cast<int>(std::floor(x));
		int zFloor = static_cast<int>(std::floor(z));

		tX = x - xFloor;
		tZ = z - zFloor;

		unsigned int x0 = xFloor & m_periodMask;
		unsigned int x1 = (x0 + 1) & m_periodMask;
		unsigned int z0 = zFloor & m_periodMask;
		unsigned int z1 = (z0 + 1) & m_periodMask;

		index00 = hash(x0, z0);
		index01 = hash(x0, z1);
		index10 = hash(x1, z0);
		index11 = hash(x1, z1);
	}

	template <unsigned int periodExponent>
	float Noise<periodExponent>::smoothstep(float t)
	{
		return ((6 * t - 15) * t + 10) * t * t * t;
	}

	template <unsigned int periodExponent>
	float Noise<periodExponent>::smoothstepDeriv(float t)
	{
		return ((30 * t - 60) * t + 30) * t * t;
	}

	template <unsigned int periodExponent>
	float Noise<periodExponent>::lerp(float valueStart, float valueEnd, float t)
	{
		return (1 - t) * valueStart + t * valueEnd;
	}

	template <unsigned int periodExponent>
	std::size_t Noise<periodExponent>::hash(unsigned int x, unsigned int z) const
	{
		return m_permutation[m_permutation[x] + z];
	}
}
