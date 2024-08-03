add_library(field field.cpp field.h sandpile.cpp sandpile.h point.h)
target_include_directories(field PUBLIC ${PROJECT_SOURCE_DIR})
