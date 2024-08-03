#include "sandpile.h"

bool Sandpile::IsCompleted() {
	for (uint16_t i = 0; i < field.height; ++i) {
		for (uint16_t j = 0; j < field.width; ++j) {
			if (field.field[i][j] >= black_code) {
				return false;
			}
		}
	}
	return true;
}

bool Sandpile::IsRightExpansion() {
	for (uint16_t i = 0; i < field.height; ++i) {
		if (field.field[i][field.width - 1] >= black_code - 1) {
			return true; 
		}
	}
	return false;
}

bool Sandpile::IsLeftExpansion() {
	for (uint16_t i = 0; i < field.height; ++i) {
		if (field.field[i][0] >= black_code - 1) {
			return true; 
		}
	}
	return false;
}

bool Sandpile::IsUpExpansion() {
	for (uint16_t i = 0; i < field.width; ++i) {
		if (field.field[0][i] >= black_code - 1) {
			return true; 
		}
	}
	return false;
}

bool Sandpile::IsDownExpansion() {
	for (uint16_t i = 0; i < field.width; ++i) {
		if (field.field[field.height - 1][i] >= black_code - 1) {
			return true; 
		}
	}
	return false;
}

void Sandpile::SandMove() {
	for (uint16_t i = 0; i < field.height; ++i) {
		for (uint16_t j = 0; j < field.width; ++j) {
			if (field.field[i][j] >= black_code) {
				field.field[i][j] -= black_code;
				++field.field[i + 1][j];
				++field.field[i - 1][j];
				++field.field[i][j + 1];
				++field.field[i][j - 1];
			}

		}
	}
}

void Sandpile::Iteration() {
	bool up = IsUpExpansion();
	bool down = IsDownExpansion();
	bool left = IsLeftExpansion();
	bool right = IsRightExpansion();

	if (up || down || left || right) {
		uint16_t x = 0;
		uint16_t y = 0;
		uint16_t new_height = field.height;
		uint16_t new_width = field.width;

		if (up) {
			y = 100;
			new_height += 100;
		}
		if (down) {
			new_height += 100;
		}
		if (left) {
			x = 100;
			new_width += 100;
		}
		if (right) {
			new_width += 100;
		}

		const int16_t starter_x = x;

		Field new_field(new_height, new_width);
		for (uint16_t i = 0; i < field.height; ++i) {
			x = starter_x;
			for (uint16_t j = 0; j < field.width; ++j) {
				new_field.field[y][x] = field.field[i][j];
				++x;
			}
			++y;
		}
		field = std::move(new_field);
	}

	SandMove();
}

void Sandpile::Cutting() {
	uint16_t left = 0;
	uint16_t right = 0;
	uint16_t up = 0;
	uint16_t down = 0;
	for (int16_t i = 0; i < field.height; ++i) {
		bool is_empty = true;
		for (int j = 0; j < field.width; ++j) {
			if (field.field[i][j] != 0) {
				is_empty = false;
				break;
			}
		}
		if (is_empty) ++up;
		else break;
	}
	for (int16_t i = field.height - 1; i >= 0; --i) {
		bool is_empty = true;
		for (int j = 0; j < field.width; ++j) {
			if (field.field[i][j] != 0) {
				is_empty = false;
				break;
			}
		}
		if (is_empty) ++down;
		else break;
	}
	for (int i = 0; i < field.width; ++i) {
		bool is_empty = true;
		for (int j = 0; j < field.height; ++j) {
			if (field.field[j][i] != 0) {
				is_empty = false;
				break;
			}
		}
		if (is_empty) ++left;
		else break;
	}
	for (int i = field.width - 1; i >= 0; --i) {
		bool is_empty = true;
		for (int j = 0; j < field.height; ++j) {
			if (field.field[j][i] != 0) {
				is_empty = false;
				break;
			}
		}
		if (is_empty) ++right;
		else break;
	}

	uint16_t x = left;
	uint16_t y = up;
	uint16_t new_height = field.height - up - down;
	uint16_t new_width = field.width - left - right;
	Field new_field(new_height, new_width);
	uint16_t starter_x = x;
	for (uint16_t i = 0; i < new_height; ++i) {
		x = starter_x;
		for (uint16_t j = 0; j < new_width; ++j) {
			new_field.field[i][j] = field.field[y][x];
			++x;
		}
		++y;
	}
	field = std::move(new_field);
}

