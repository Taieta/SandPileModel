#include "tsv_reading.h"

Field ParseTSV(const char* path) {
	uint16_t max_width = 0;
	uint16_t max_height = 0;
	uint16_t min_height = 65535;
	uint16_t min_width = 65535;
	List input;
	std::ifstream file(path, std::ios::binary);

	if (!file) {
		std::cerr << "No such file or directory for input file\n";
		exit(0);
	}

	uint16_t x;
	uint16_t y;
	uint64_t n_grains;

	while (file >> x >> y >> n_grains) {
		Point new_point (x, y, n_grains);
		max_width = std::max(max_width, x);
		max_height = std::max(max_height, y);
		min_width = std::min(min_width, x);
		min_height = std::min(min_height, y);
		input.Append(new_point);
	}

	uint16_t height = max_height - min_height + 2;
	uint16_t width = max_width - min_width + 2;
	Field field(height, width);

	while (!input.IsEnd()) {
		Point cur_point = input.Front();
		field.field[cur_point.y - min_height][cur_point.x - min_width] = cur_point.n_grains;
		input.Pop();
	}

	return field;
}
