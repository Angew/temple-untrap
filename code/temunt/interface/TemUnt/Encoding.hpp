#pragma once

#include "TemUnt/Encoding.hxx"

#include <cassert>


namespace TemUnt {

inline constexpr CodeInt Encoding::HeroMask() { return 0b111 << HeroOffset(); }
inline constexpr CodeInt Encoding::HeroOffset() { return 4; }
inline constexpr CodeInt Encoding::WaterMask() { return 0b1111 << WaterOffset(); }
inline constexpr CodeInt Encoding::WaterOffset() { return 0; }
inline constexpr CodeInt Encoding::OneTileMask() { return 0b111; }
inline constexpr CodeInt Encoding::TwoTileMask() { return 0b111'111; }
inline constexpr CodeInt Encoding::ThreeTileMask() { return 0b111'111'111; }


inline bool Encoding::isBeforeWater(CodeInt squareCode, CodeInt water)
{
	return squareCode < water;
}

inline bool Encoding::isAfterWater(CodeInt squareCode, CodeInt water)
{
	return !isBeforeWater(squareCode, water);
}


inline Code Encoding::rotate3Left(CodeInt start) const
{
	const auto rotatedTile = code & (OneTileMask() << (31-3 - 3*start));
	const auto shiftedTiles = code & (TwoTileMask() << (31-6 - 3*(start+1)));
	auto result = code & ~(ThreeTileMask() << (31-9 - 3*start));
	result |= shiftedTiles << 3;
	result |= rotatedTile >> 6;
	return result;
}

inline Code Encoding::rotate3Right(CodeInt start) const
{
	const auto rotatedTile = code & (OneTileMask() << (31-3 - 3*(start+2)));
	const auto shiftedTiles = code & (TwoTileMask() << (31-6 - 3*start));
	auto result = code & ~(ThreeTileMask() << (31-9 - 3*start));
	result |= shiftedTiles >> 3;
	result |= rotatedTile << 6;
	return result;
}


inline Encoding::Encoding(Code code) : code{code}
{}

inline CodeInt Encoding::getHeroSquareCode() const
{
	return (code & HeroMask()) >> HeroOffset();
}

inline unsigned int Encoding::getTileIndex(CodeInt squareCode) const
{
	const CodeInt offset = 31-3 - 3*squareCode;
	const CodeInt mask = OneTileMask() << offset;
	return (code & mask) >> offset;
}

inline CodeInt Encoding::getWaterSquare() const
{
	return (code & WaterMask()) >> WaterOffset();
}

template <Direction Dir>
Code Encoding::moveHero() const
{
	auto hero = getHeroSquareCode();
	if constexpr(Dir == Direction::North) {
		const auto water = getWaterSquare();
		assert(hero != water + 3 && "Cannot move North into water");
		if (hero >= water && hero < water+3) {
			hero -= 2;
		} else {
			hero -= 3;
		}
	} else if constexpr (Dir == Direction::South) {
		const auto water = getWaterSquare();
		assert(hero + 3 != water && "Cannot move South into water");
		if (hero < water && hero+3 > water) {
			hero += 2;
		} else {
			hero += 3;
		}
	} else if constexpr (Dir == Direction::East) {
		hero += 1;
	} else if constexpr (Dir == Direction::West) {
		hero -= 1;
	} else {
		static_assert(false, "Unsupported Dir argument");
	}
	return (code & ~HeroMask()) | (hero << HeroOffset());
}

template <Direction Dir>
Code Encoding::moveWater() const
{
	const auto water = getWaterSquare();
	if constexpr (Dir == Direction::East) {
		return (code & ~WaterMask()) | ((water+1) << WaterOffset());
	}
	if constexpr (Dir == Direction::West) {
		return (code & ~WaterMask()) | ((water - 1) << WaterOffset());
	}
	const auto hero = getHeroSquareCode();
	auto newHero = hero;
	auto newWater = water;
	auto newCode = code;
	if constexpr (Dir == Direction::North) {
		newWater = water - 3;
		if (isBeforeWater(hero, water) && isAfterWater(hero, newWater)) {
			newHero -= 1;
		}
		newCode = rotate3Left(newWater);
	} else if constexpr (Dir == Direction::South) {
		newWater = water + 3;
		if (isAfterWater(hero, water) && isBeforeWater(hero, newWater)) {
			newHero += 1;
		}
		newCode = rotate3Right(water);
	} else if constexpr (Dir != Direction::East && Dir != Direction::West) {
		static_assert(false, "Unsupported Dir argument");
	}
	assert(newCode != code);
	if (newHero != hero) {
		newCode = (newCode & ~HeroMask()) | (newHero << HeroOffset());
	}
	assert(newWater != water);
	return (newCode & ~WaterMask()) | (newWater << WaterOffset());
}

} //namespace TemUnt
