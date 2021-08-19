#pragma once

#include "TemUnt/Direction.hh"
#include "TemUnt/TileEdge.hxx"

#include <array>


namespace TemUnt {

class Tile
{
	std::array<TileEdge, 4> edges;

public:
	TileEdge getEdge(Direction dir) const;
};

} //namespace TemUnt
