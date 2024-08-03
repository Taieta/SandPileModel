cmake_minimum_required(VERSION 3.12)

project(
	SandPile
	VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(bin)
add_subdirectory(drawing)
add_subdirectory(field)
add_subdirectory(reading)
