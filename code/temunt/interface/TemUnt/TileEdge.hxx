#pragma once

#include "TemUnt/TileEdge.hh"


namespace TemUnt {

enum class TileEdge
{
	Wall = 1 << 0,
	LowFloor = 1 << 1,
	HighFloor = 1 << 2,
	Stairs = 1 << 3
};

} //namespace TemUnt
