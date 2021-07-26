#include "TemUnt/SituationBuilder.hpp"

#include "TemUnt/Encoding.hpp"

#include <cassert>


namespace TemUnt {

bool SituationBuilder::isComplete() const
{
	return false;
}


void SituationBuilder::setWaterCoords(int x, int y)
{
	assert(0 <= x && x <= 2);
	assert(0 <= y && y <= 2);
	code &= ~CodeBuilder(Encoding::WaterMask());
	code |= CodeBuilder(x) << Encoding::WaterXOffset();
	code |= CodeBuilder(y) << Encoding::WaterYOffset();
}

} //namespace TemUnt
