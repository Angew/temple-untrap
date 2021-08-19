#pragma once

#include "TemUnt/Situation.hxx"

#include "TemUnt/Encoding.hpp"


namespace TemUnt {

inline Situation::Situation(Code code) :
	encoding{code}
{}


inline Situation Situation::fromCode(Code code)
{
	return {code};
}

inline Code Situation::getCode() const
{
	return encoding.getCode();
}

} //namespace TemUnt
