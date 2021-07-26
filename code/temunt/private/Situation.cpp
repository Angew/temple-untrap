#include "TemUnt/Situation.hpp"


namespace TemUnt {

Situation::NeighbourEnumerator::NeighbourEnumerator() :
	end_{&neighbours.front()}
{}


auto Situation::iterateNeighbours() -> NeighbourEnumerator
{
	NeighbourEnumerator neighbours;
	Encoding encoding{code};
	const auto heroSquareCode = encoding.getHeroSquareCode();
	const auto heroTile = tileDatabase->getTile(encoding.getTileIndex(heroSquareCode));
	const auto heroSquare = decodeSquare(heroSquareCode);
	// Hero moves
	{
		int moves = 0;
		if (heroSquare > 2) {
			if (testPassable(heroTile, Direction::North, heroSquare - 3, Direction::South)) {
				neighbours.addNeighbour(encoding.moveHeroNorth());
				++moves;
			}
		}
		if (heroSquare < 6) {
			if (testPassable(heroTile, Direction::South, heroSquare + 3, Direction::North)) {
				neighbours.addNeighbour(encoding.moveHeroSouth());
				++moves;
			}
		}
		if (moves < 2 && (heroSquare % 3 < 2)) {
			if (testPassable(heroTile, Direction::East, heroSquare + 1, Direction::West)) {
				neighbours.addNeighbour(encoding.moveHeroEast());
				++moves;
			}
		}
		if (moves < 2 && (heroSquare % 3 > 0)) {
			if (testPassable(heroTile, Direction::West, heroSquare - 1, Direction::East)) {
				neighbours.addNeighbour(encoding.moveHeroWest());
				++moves;
			}
		}
	}
	// Water moves
	{
		const auto waterSquare = encoding.getWaterSquare();
		if (waterSquare > 2 && waterSquare - 3 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWaterNorth());
		}
		if (waterSquare < 6 && waterSquare + 3 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWaterSouth());
		}
		if (waterSquare % 3 < 2 && waterSquare + 1 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWaterEast());
		}
		if (waterSquare % 3 > 0 && waterSquare - 1 != heroSquare) {
			neighbours.addNeighbour(encoding.moveWaterWest());
		}
	}
	// Done
	return neighbours;
}

} //namespace TemUnt
