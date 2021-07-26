#define BOOST_TEST_MODULE Temple Untrap
#include <boost/test/included/unit_test.hpp>


#include "TemUnt/SituationBuilder.hpp"


BOOST_AUTO_TEST_CASE(SituationBuilder)
{
	auto builder = TemUnt::SituationBuilder{};
	BOOST_CHECK(!builder.isComplete());
	builder.setWaterCoords(0, 0);
	BOOST_CHECK(!builder.isComplete());
}
