#pragma once

#include "TemUnt/Situation.hxx"


namespace TemUnt {

inline Situation::Situation(Code code) :
	code{code}
{}


inline Situation Situation::fromCode(Code code)
{
	return {code};
}

} //namespace TemUnt
