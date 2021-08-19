#pragma once

#include "TemUnt/Code.hxx"
#include "TemUnt/Direction.hh"
#include "TemUnt/Encoding.hxx"
#include "TemUnt/Tile.hh"
#include "TemUnt/TileDatabase.hh"

#include <array>


namespace TemUnt {

class Situation
{
	Encoding encoding;
	CodeInt waterSquare{~0u};
	const TileDatabase *tileDatabase;

	Situation(Code code);

	void decodeWaterSquare();
	CodeInt decodeSquare(CodeInt squareCode) const;
	CodeInt encodeSquare(CodeInt square) const;

	bool testPassable(Tile tile1, Direction dir1, CodeInt square2, Direction dir2) const;
	bool testPassable(Tile tile1, Direction dir1, Tile tile2, Direction dir2) const;

public:
	static Situation fromCode(Code code);

	class NeighbourEnumerator
	{
		friend class Situation;

		std::array<Code, 6> neighbours;
		Code* end_;

		NeighbourEnumerator();

		void addNeighbour(Code neighbour);

	public:
		const Code* begin() const { return &neighbours.front(); }
		const Code* end() const { return end_; }
	};

	NeighbourEnumerator iterateNeighbours();

	Code getCode() const;
};

} //namespace TemUnt
