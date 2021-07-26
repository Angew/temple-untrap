add_library(TemUnt STATIC
	private/SituationBuilder.cpp
)
foreach(header
	Code
	Encoding
	SituationBuilder
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

target_link_libraries(TemUnt
	PRIVATE
		WarningFree
)
