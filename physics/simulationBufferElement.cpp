#include "physics/simulationBufferElement.hpp"

#include "common/mapName.hpp"

namespace Physics
{
	SimulationBufferElement::SimulationBufferElement(Common::MapName mapName) :
		scene{mapName}
	{ }
}
