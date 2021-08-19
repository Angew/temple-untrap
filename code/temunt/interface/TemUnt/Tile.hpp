#pragma once

#include "TemUnt/Tile.hxx"

#include "TemUnt/Direction.hpp"


namespace TemUnt {

TileEdge Tile::getEdge(Direction dir) const
{
	return edges[static_cast<DirectionIndex>(dir)];
}

} //namespace TemUnt
