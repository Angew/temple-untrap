add_executable(Solver
	code/main.cpp
)

target_link_libraries(Solver
	PRIVATE
		TemUnt
		WarningFree
)
