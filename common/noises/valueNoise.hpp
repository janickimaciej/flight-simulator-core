#pragma once

#include "common/noises/noise.hpp"

#include <array>
#include <cstddef>
#include <random>

namespace Common
{
	template <unsigned int periodExponent>
	class ValueNoise : public Noise<periodExponent>
	{
		using Noise<periodExponent>::m_period;

	public:
		ValueNoise(unsigned int seed);
		virtual ~ValueNoise() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		std::array<float, m_period> m_values{};
	};

	template <unsigned int periodExponent>
	ValueNoise<periodExponent>::ValueNoise(unsigned int seed) :
		Noise<periodExponent>{seed}
	{
		std::mt19937 generator{seed};

		std::uniform_real_distribution<float> floatDistribution{0, 1};
		for (std::size_t i = 0; i < m_period; ++i)
		{
			m_values[i] = floatDistribution(generator);
		}
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::height(float x, float z) const
	{
		float tX{};
		float tZ{};
		std::size_t index00{};
		std::size_t index01{};
		std::size_t index10{};
		std::size_t index11{};
		this->common(x, z, tX, tZ, index00, index01, index10, index11);

		float smoothTX = this->smoothstep(tX);
		float smoothTZ = this->smoothstep(tZ);
		
		float y00 = m_values[index00];
		float y01 = m_values[index01];
		float y10 = m_values[index10];
		float y11 = m_values[index11];

		float lerp0 = this->lerp(y00, y10, smoothTX);
		float lerp1 = this->lerp(y01, y11, smoothTX);

		return this->lerp(lerp0, lerp1, smoothTZ);
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::heightDerivX(float x, float z) const
	{
		float tX{};
		float tZ{};
		std::size_t index00{};
		std::size_t index01{};
		std::size_t index10{};
		std::size_t index11{};
		this->common(x, z, tX, tZ, index00, index01, index10, index11);

		float smoothTZ = this->smoothstep(tZ);
		
		float smoothDerivTX = this->smoothstepDeriv(tX);
		
		float y00 = m_values[index00];
		float y01 = m_values[index01];
		float y10 = m_values[index10];
		float y11 = m_values[index11];

		float lerp0DerivX = smoothDerivTX * (y10 - y00);
		float lerp1DerivX = smoothDerivTX * (y11 - y01);

		return this->lerp(lerp0DerivX, lerp1DerivX, smoothTZ);
	}

	template <unsigned int periodExponent>
	float ValueNoise<periodExponent>::heightDerivZ(float x, float z) const
	{
		float tX{};
		float tZ{};
		std::size_t index00{};
		std::size_t index01{};
		std::size_t index10{};
		std::size_t index11{};
		this->common(x, z, tX, tZ, index00, index01, index10, index11);

		float smoothTX = this->smoothstep(tX);

		float smoothDerivTZ = this->smoothstepDeriv(tZ);
		
		float y00 = m_values[index00];
		float y01 = m_values[index01];
		float y10 = m_values[index10];
		float y11 = m_values[index11];

		float lerp0 = this->lerp(y00, y10, smoothTX);
		float lerp1 = this->lerp(y01, y11, smoothTX);

		return smoothDerivTZ * (lerp1 - lerp0);
	}
}
