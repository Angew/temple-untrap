#pragma once

#include "TemUnt/Code.hxx"

#include <array>


namespace TemUnt {

class Situation
{
	Code code;

	Situation(Code code);

public:
	static Situation fromCode(Code code);

	class NeighbourEnumerator
	{
		friend class Situation;

		std::array<Code, 6> neighbours;
		const Code* end_;

		NeighbourEnumerator();

		void addNeighbour(Code neighbour);

	public:
		const Code* begin() const { return &neighbours.front(); }
		const Code* end() const { return end_; }
	};

	NeighbourEnumerator iterateNeighbours();

	Code getCode() const { return code; }
};

} //namespace TemUnt
