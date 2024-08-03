#pragma once
#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>
#include <random>
#include "reading/args_reading.h"
#include "field/field.h"

struct Color {
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
};

const Color kBlack = Color(0, 0, 0);
const Color kYellow = Color(255, 195, 0);
const Color kGreen = Color(166, 226, 60);
const Color kViolet = Color(159, 22, 214);
const Color kWhite = Color(255, 255, 255);
const Color kBlue = Color(62, 199, 205);
const Color kRed = Color(224, 69, 64);

const uint64_t kFileHeaderSize = 14;
const uint64_t kInformationHeaderSize = 40;
const uint64_t kTotalColors = 5;
const uint64_t kBitsPerPixel = 4;
const uint64_t kColorBytes = 4;
const uint64_t kPalleteSize = kColorBytes * kTotalColors;

uint8_t GetRandomByte();
void ToImage (const Field& field, const Arguments& user_input, const uint64_t& cur_iter);
