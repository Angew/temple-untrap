#pragma once

#include <bitset>

namespace TemUnt {

class SituationBuilder
{
	using CodeBuilder = std::bitset<32>;
	CodeBuilder code;

public:
	SituationBuilder() = default;

	bool isComplete() const;

	void setWaterCoords(int x, int y);
};

} //namespace TemUnt
