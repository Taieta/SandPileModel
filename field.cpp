#include "field.h"

Field::Field(uint16_t& height_, uint16_t& width_) {
	height = height_;
	width = width_;
	field = new uint64_t* [height];
	for (uint16_t i = 0; i < height; ++i) {
		field[i] = new uint64_t[width];
		for (uint16_t j = 0; j < width; ++j) {
			field[i][j] = 0;
		}
	}
}

Field::Field(Field&& other) {
	height = other.height;
	width = other.width;
	field = other.field;

	other.height = 0;
	other.width = 0;
	other.field = nullptr;
}

Field& Field::operator=(Field&& other) {
	if (this != &other) {
		for (uint16_t i = 0; i < height; ++i) {
			delete[] field[i];
		}
		delete[] field;

		height = other.height;
		width = other.width;
		field = other.field;

		other.height = 0;
		other.width = 0;
		other.field = nullptr;
	}

	return *this;
}

Field::~Field() {
	for (uint16_t i = 0; i < height; ++i) {
		delete[] field[i];
	}
	delete[] field;
}
