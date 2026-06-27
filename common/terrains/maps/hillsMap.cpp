#include "common/terrains/maps/hillsMap.hpp"

#include "common/terrains/valueNoise.hpp"

#include <memory>

namespace Common::Terrains
{
	static constexpr float lengthX = 20000;
	static constexpr float lengthZ = 20000;
	static constexpr float spacingX = 50;
	static constexpr float spacingZ = 50;

	HillsMap::HillsMap() :
		Map{lengthX, lengthZ, spacingX, spacingZ}
	{
		m_elements.push_back(std::make_unique<ValueNoise>(0.00012f, 2048, 0));
		m_elements.push_back(std::make_unique<ValueNoise>(0.00025f, 1024, 0));
		m_elements.push_back(std::make_unique<ValueNoise>(0.0005f, 512, 0));
		m_elements.push_back(std::make_unique<ValueNoise>(0.001f, 256, 0));
		m_elements.push_back(std::make_unique<ValueNoise>(0.002f, 128, 0));
		m_elements.push_back(std::make_unique<ValueNoise>(0.004f, 64, 0));
		m_elements.push_back(std::make_unique<ValueNoise>(0.008f, 32, 0));
	}
	
	float HillsMap::getMaxHeight() const
	{
		return 4100;
	}
}
