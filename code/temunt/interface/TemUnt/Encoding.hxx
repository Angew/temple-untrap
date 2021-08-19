#pragma once

#include "TemUnt/Code.hxx"
#include "TemUnt/Direction.hxx"


namespace TemUnt {

class Encoding
{
	Code code;

	static constexpr CodeInt HeroMask();
	static constexpr CodeInt HeroOffset();
	static constexpr CodeInt WaterMask();
	static constexpr CodeInt WaterOffset();
	static constexpr CodeInt OneTileMask();
	static constexpr CodeInt TwoTileMask();
	static constexpr CodeInt ThreeTileMask();

	static bool isBeforeWater(CodeInt squareCode, CodeInt water);
	static bool isAfterWater(CodeInt squareCode, CodeInt water);

	Code rotate3Left(CodeInt start) const;
	Code rotate3Right(CodeInt start) const;

public:
	static constexpr Code StartState() { return 0b0111'1111'1111'1111'1111'1111'1111'1111; }
	static constexpr Code Victory() { return 0b0000'1111'1111'1111'1111'1111'1111'1111; }

	Encoding(Code code);

	Code getCode() const { return code; }

	CodeInt getHeroSquareCode() const;
	unsigned int getTileIndex(CodeInt squareCode) const;
	CodeInt getWaterSquare() const;

	template <Direction Dir>
	Code moveHero() const;
	template <Direction Dir>
	Code moveWater() const;
};

} //namespace TemUnt
