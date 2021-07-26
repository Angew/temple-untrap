#pragma once

#include "TemUnt/Code.hxx"


namespace TemUnt {

struct Encoding
{
	static constexpr unsigned int WaterMask() { return 0b1111; }

	static constexpr unsigned int WaterXOffset() { return 0; }
	static constexpr unsigned int WaterYOffset() { return 2; }

	static constexpr Code StartState() { return 0b0111'1111'1111'1111'1111'1111'1111'1111; }
	static constexpr Code Victory() { return 0b0000'1111'1111'1111'1111'1111'1111'1111; }
};

} //namespace TemUnt
