cmake_minimum_required(VERSION 3.13)
project(TempleUntrap)


# Boost
find_package(Boost 1.66 REQUIRED)
target_compile_definitions(Boost::boost INTERFACE BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
#include(BoostTestWrapper.cmake)


# Config
add_library(WarningFree INTERFACE)
if(MSVC)
	target_compile_options(WarningFree INTERFACE /WX)
endif()


# Code
add_subdirectory(solver)
add_subdirectory(temunt)
add_subdirectory(test)
