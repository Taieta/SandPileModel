add_library(reading args_reading.cpp args_reading.h list.cpp list.h tsv_reading.cpp tsv_reading.h)
target_include_directories(reading PUBLIC ${PROJECT_SOURCE_DIR})
