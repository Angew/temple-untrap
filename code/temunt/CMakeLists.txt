add_library(TemUnt STATIC
	private/Situation.cpp
)
foreach(header
	Code
	Direction
	Encoding
	Situation
	Tile
	TileDatabase
	TileEdge
)
	target_sources(TemUnt PRIVATE
		interface/TemUnt/${header}.hh
		interface/TemUnt/${header}.hxx
		interface/TemUnt/${header}.hpp
	)
endforeach()

target_include_directories(TemUnt
	PUBLIC
		interface
)

target_compile_features(TemUnt
	PUBLIC
		cxx_std_17
)

target_link_libraries(TemUnt
	PUBLIC
		Boost::boost
	PRIVATE
		WarningFree
)
