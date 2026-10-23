#pragma once

#include "common/noises/noise.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <cmath>
#include <cstddef>
#include <random>

namespace Common
{
	template <unsigned int periodExponent>
	class PerlinNoise : public Noise<periodExponent>
	{
		using Noise<periodExponent>::m_period;

	public:
		PerlinNoise(unsigned int seed);
		virtual ~PerlinNoise() = default;

		virtual float height(float x, float z) const override;
		virtual float heightDerivX(float x, float z) const override;
		virtual float heightDerivZ(float x, float z) const override;

	private:
		std::array<glm::vec2, m_period> m_gradients{};
	};

	template <unsigned int periodExponent>
	PerlinNoise<periodExponent>::PerlinNoise(unsigned int seed) :
		Noise<periodExponent>{seed}
	{
		std::mt19937 generator{seed};

		std::uniform_real_distribution<float> floatDistribution{0, 1};
		for (std::size_t i = 0; i < m_period; ++i)
		{
			float phi = 2 * glm::pi<float>() * floatDistribution(generator);
			m_gradients[i] = {std::cos(phi), -std::sin(phi)};
		}
	}

	template <unsigned int periodExponent>
	float PerlinNoise<periodExponent>::height(float x, float z) const
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

		float y00 = glm::dot({tX, tZ}, m_gradients[index00]);
		float y01 = glm::dot({tX, tZ - 1}, m_gradients[index01]);
		float y10 = glm::dot({tX - 1, tZ}, m_gradients[index10]);
		float y11 = glm::dot({tX - 1, tZ - 1}, m_gradients[index11]);

		float lerp0 = this->lerp(y00, y10, smoothTX);
		float lerp1 = this->lerp(y01, y11, smoothTX);

		return std::sqrt(0.5f) * this->lerp(lerp0, lerp1, smoothTZ) + 0.5f;
	}

	template <unsigned int periodExponent>
	float PerlinNoise<periodExponent>::heightDerivX(float x, float z) const
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

		float smoothDerivTX = this->smoothstepDeriv(tX);

		float y00 = glm::dot({tX, tZ}, m_gradients[index00]);
		float y01 = glm::dot({tX, tZ - 1}, m_gradients[index01]);
		float y10 = glm::dot({tX - 1, tZ}, m_gradients[index10]);
		float y11 = glm::dot({tX - 1, tZ - 1}, m_gradients[index11]);

		float y00DerivX = m_gradients[index00].x;
		float y01DerivX = m_gradients[index01].x;
		float y10DerivX = m_gradients[index10].x;
		float y11DerivX = m_gradients[index11].x;

		float lerp0DerivX = smoothDerivTX * (y10 - y00) +
			this->lerp(y00DerivX, y10DerivX, smoothTX);
		float lerp1DerivX = smoothDerivTX * (y11 - y01) +
			this->lerp(y01DerivX, y11DerivX, smoothTX);

		return std::sqrt(0.5f) * this->lerp(lerp0DerivX, lerp1DerivX, smoothTZ);
	}

	template <unsigned int periodExponent>
	float PerlinNoise<periodExponent>::heightDerivZ(float x, float z) const
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

		float smoothDerivTZ = this->smoothstepDeriv(tZ);

		float y00 = glm::dot({tX, tZ}, m_gradients[index00]);
		float y01 = glm::dot({tX, tZ - 1}, m_gradients[index01]);
		float y10 = glm::dot({tX - 1, tZ}, m_gradients[index10]);
		float y11 = glm::dot({tX - 1, tZ - 1}, m_gradients[index11]);

		float y00DerivZ = m_gradients[index00].y;
		float y01DerivZ = m_gradients[index01].y;
		float y10DerivZ = m_gradients[index10].y;
		float y11DerivZ = m_gradients[index11].y;

		float lerp0 = this->lerp(y00, y10, smoothTX);
		float lerp1 = this->lerp(y01, y11, smoothTX);

		float lerp0DerivZ = this->lerp(y00DerivZ, y10DerivZ, smoothTX);
		float lerp1DerivZ = this->lerp(y01DerivZ, y11DerivZ, smoothTX);

		return std::sqrt(0.5f) * (smoothDerivTZ * (lerp1 - lerp0) +
			this->lerp(lerp0DerivZ, lerp1DerivZ, smoothTZ));
	}
}
