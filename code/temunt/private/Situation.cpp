#include "TemUnt/Situation.hpp"

#include "TemUnt/Direction.hpp"
#include "TemUnt/Encoding.hpp"
#include "TemUnt/Tile.hpp"
#include "TemUnt/TileDatabase.hpp"
#include "TemUnt/TileEdge.hpp"

#include <boost/operators.hpp>

#include <cassert>

#include <functional>
#include <type_traits>
#include <unordered_set>


namespace TemUnt {

class TileEdgePair : boost::equality_comparable<TileEdgePair>
{
	using Data = std::underlying_type_t<TileEdge>;
	Data data;

public:
	TileEdgePair(TileEdge a, TileEdge b) : data{static_cast<Data>(a) | static_cast<Data>(b)}
	{}

	friend bool operator== (TileEdgePair lhs, TileEdgePair rhs)
	{ return lhs.data == rhs.data; }

	auto hash() const
	{ return std::hash<Data>{}(data); }
};

} //namespace TemUnt

namespace std {

template <>
struct hash<TemUnt::TileEdgePair>
{
	auto operator() (TemUnt::TileEdgePair arg) const
	{ return arg.hash(); }
};

} //namespace std


namespace TemUnt {

Situation::NeighbourEnumerator::NeighbourEnumerator() :
	end_{&neighbours.front()}
{}

void Situation::NeighbourEnumerator::addNeighbour(Code neighbour)
{
	*end_++ = neighbour;
}


void Situation::decodeWaterSquare()
{
	waterSquare = encoding.getWaterSquare();
}

CodeInt Situation::decodeSquare(CodeInt squareCode) const
{
	assert(waterSquare < 9 && "waterSquare wasn't initialised before calling decodeSquare()");
	if (squareCode < waterSquare) {
		return squareCode;
	} else {
		return squareCode + 1;
	}
}

CodeInt Situation::encodeSquare(CodeInt square) const
{
	assert(waterSquare < 9 && "waterSquare wasn't initialised before calling encodeSquare()");
	assert(square != waterSquare && "Water's square can't be encoded");
	if (square < waterSquare) {
		return square;
	} else {
		return square - 1;
	}
}

bool Situation::testPassable(Tile tile1, Direction dir1, CodeInt square2, Direction dir2) const
{
	return testPassable(
		tile1, dir1,
		tileDatabase->getTile(encoding.getTileIndex(encodeSquare(square2))), dir2
	);
}

bool Situation::testPassable(Tile tile1, Direction dir1, Tile tile2, Direction dir2) const
{
	static const std::unordered_set<TileEdgePair> passablePairs {
		{TileEdge::HighFloor, TileEdge::HighFloor},
		{TileEdge::LowFloor, TileEdge::LowFloor},
		{TileEdge::HighFloor, TileEdge::Stairs}
	};
	return passablePairs.find({tile1.getEdge(dir1), tile2.getEdge(dir2)}) != passablePairs.end();
}

auto Situation::iterateNeighbours() -> NeighbourEnumerator
{
	NeighbourEnumerator neighbours;
	decodeWaterSquare();
	const auto heroSquareCode = encoding.getHeroSquareCode();
	const auto heroTile = tileDatabase->getTile(encoding.getTileIndex(heroSquareCode));
	const auto heroSquare = decodeSquare(heroSquareCode);
	// Hero moves
	{
		int moves = 0;
		if (heroSquare > 2) {
			if (testPassable(heroTile, Direction::North, heroSquare - 3, Direction::South)) {
				neighbours.addNeighbour(encoding.moveHero<Direction::North>());
				++moves;
			}
		}
		if (heroSquare < 6) {
			if (testPassable(heroTile, Direction::South, heroSquare + 3, Direction::North)) {
				neighbours.addNeighbour(encoding.moveHero<Direction::South>());
				++moves;
			}
		}
		if (moves < 2 && (heroSquare % 3 < 2)) {
			if (testPassable(heroTile, Direction::East, heroSquare + 1, Direction::West)) {
				neighbours.addNeighbour(encoding.moveHero<Direction::East>());
				++moves;
			}
		}
		if (moves < 2) {
			if (heroSquare % 3 > 0) {
				if (testPassable(heroTile, Direction::West, heroSquare - 1, Direction::East)) {
					neighbours.addNeighbour(encoding.moveHero<Direction::West>());
					++moves;
				}
			} else if (heroSquare == 0) {
				if (testPassable(heroTile, Direction::West, tileDatabase->getExitTile(), Direction::East)) {
					neighbours.addNeighbour(Encoding::Victory());
					++moves;
				}
			}
		}
	}
	// Water moves
	{
		if (waterSquare > 2 && waterSquare - 3 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWater<Direction::North>());
		}
		if (waterSquare < 6 && waterSquare + 3 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWater<Direction::South>());
		}
		if (waterSquare % 3 < 2 && waterSquare + 1 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWater<Direction::East>());
		}
		if (waterSquare % 3 > 0 && waterSquare - 1 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWater<Direction::West>());
		}
	}
	// Done
	return neighbours;
}

} //namespace TemUnt
