#pragma once

#include "TemUnt/Tile.hxx"


namespace TemUnt {

class TileDatabase
{
	std::array<Tile, 8> tiles;
	Tile exitTile;

public:
	Tile getTile(unsigned int index) const;
	Tile getExitTile() const;
};

} //namespace TemUnt
