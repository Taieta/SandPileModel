#pragma once
#include <cstdint>
#include <iostream>

struct Field {
public:
	uint16_t height;
	uint16_t width;
	uint64_t** field;
	Field(uint16_t& height_, uint16_t& width_);
	Field(Field& other) = delete;
	Field(Field&& other);
	Field& operator=(Field& other) = delete;
	Field& operator=(Field&& other);
	~Field();
};
