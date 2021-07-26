#pragma once

namespace TemUnt {

struct Encoding
{
	static constexpr unsigned int WaterMask() { return 0b1111; }

	static constexpr unsigned int WaterXOffset() { return 0; }
	static constexpr unsigned int WaterYOffset() { return 2; }
};

} //namespace TemUnt
