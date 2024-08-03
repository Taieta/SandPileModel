#include "image.h"

uint8_t GetRandomByte() {
	std::random_device rd;
	std::mt19937 gen{rd()};
	return gen() % 256;
}

void ToImage(const Field& field, const Arguments& user_input, const uint64_t& cur_iter) {
	std::string iter = std::to_string(cur_iter);
	std::string path_start(user_input.path);
	std::string path = path_start + "iteration_" + iter + ".bmp";
	std::ofstream file(path, std::ios::out | std::ios::binary);

	if (!file) {
		std::cerr << "No such file or directory for output file\n";
		exit(0);
	}

	const uint64_t padding = (8 - (field.width % 8)) % 8;
	const uint64_t full_width = field.width + padding;

	const uint64_t fileSize = kFileHeaderSize + kInformationHeaderSize + kPalleteSize + (full_width * field.height) / 2;
	uint8_t fileHeader[kFileHeaderSize] = {};
	uint8_t informationHeader[kInformationHeaderSize] = {};

	//file type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';
	//file size
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;
	//reserved
	fileHeader[6] = 0;
	fileHeader[7] = 0;
	fileHeader[8] = 0;
	fileHeader[9] = 0;
	//number of bytes between start of file and the first byte of pixel data
	fileHeader[10] = kFileHeaderSize + kInformationHeaderSize + kPalleteSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;
	//information_header size
	informationHeader[0] = kInformationHeaderSize;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;
	//width of image
	informationHeader[4] = field.width;
	informationHeader[5] = field.width >> 8;
	informationHeader[6] = field.width >> 16;
	informationHeader[7] = field.width >> 24;
	//height of image
	informationHeader[8] = field.height;
	informationHeader[9] = field.height >> 8;
	informationHeader[10] = field.height >> 16;
	informationHeader[11] = field.height >> 24;
	//planes
	informationHeader[12] = 1;
	informationHeader[13] = 0;
	//bits per pixel
	informationHeader[14] = kBitsPerPixel;
	informationHeader[15] = 0;
	//total colors: black, white, green, purple, yellow
	informationHeader[32] = kTotalColors;
	informationHeader[33] = 0;
	informationHeader[34] = 0;
	informationHeader[35] = 0;

	uint8_t colorPallete[kPalleteSize] = {};
	for (uint8_t i = 0; i < 20; i += 4) {
		for (uint8_t j = 0; j < 3; ++j) {
			colorPallete[i + j] = GetRandomByte();
		}
		colorPallete[i + 4] = 0;
	}
	//0 - white
	//colorPallete[0] = kWhite.b;
	//colorPallete[1] = kWhite.g;
	//colorPallete[2] = kWhite.r;
	//colorPallete[3] = 0;
	//1 - green
	//colorPallete[4] = kGreen.b;
	//colorPallete[5] = kGreen.g;
	//colorPallete[6] = kGreen.r;
	//colorPallete[7] = 0;
	//2 - purple
	//colorPallete[8] = kBlue.b;
	//colorPallete[9] = kBlue.g;
	//colorPallete[10] = kBlue.r;
	//colorPallete[11] = 0;
	//3 - yellow
	//colorPallete[12] = kRed.b;
	//colorPallete[13] = kRed.g;
	//colorPallete[14] = kRed.r;
	//colorPallete[15] = 0;
	//4 - black
	//colorPallete[16] = kBlack.b;
	//colorPallete[17] = kBlack.g;
	//colorPallete[18] = kBlack.r;
	//colorPallete[19] = 0;
	
	file.write(reinterpret_cast<char*>(fileHeader), kFileHeaderSize);
	file.write(reinterpret_cast<char*>(informationHeader), kInformationHeaderSize);
	file.write(reinterpret_cast<char*>(colorPallete), kPalleteSize);

	uint64_t first_color, second_color;
	uint8_t total_color;
	for (int64_t x = field.height - 1; x >= 0; x--) {
		for (int64_t y = 0; y < full_width; y += 2) {
			if (y >= field.width) {
				first_color = 0;
				second_color = 0;
			} else if (y + 1 >= field.width) {
				first_color = field.field[x][y];
				second_color = 0;
			} else {
				first_color = field.field[x][y];
				second_color = field.field[x][y + 1];
			}

			if (first_color >= 4) {
				first_color = 4;
			}
			if (second_color >= 4) {
				second_color = 4;
			}

			total_color = (first_color << kBitsPerPixel);
			total_color += second_color;

			file << total_color;
		}
	}

	return;
}
