#pragma once

#include "TemUnt/TileDatabase.hxx"


namespace TemUnt {

Tile TileDatabase::getTile(unsigned int index) const
{
	return tiles[index];
}

Tile TileDatabase::getExitTile() const
{
	return exitTile;
}

} //namespace TemUnt
