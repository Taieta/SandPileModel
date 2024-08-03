cmake_minimum_required(VERSION 3.12)

project(
	SandPile
	VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)

add_executable(SandPile args_reading.cpp args_reading.h field.cpp field.h main.cpp main.h image.cpp image.h tsv_reading.cpp tsv_reading.h sandpile.h sandpile.cpp list.cpp list.h point.h)
