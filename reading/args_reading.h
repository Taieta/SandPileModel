#pragma once
#include <optional>
#include <cstring>
#include <cstdint>
#include <iostream>

struct Arguments {
	const char* input = nullptr;
	const char* path = nullptr;
	uint64_t max_iter = 0;
	uint64_t freq = 0;
	bool is_error = 0;
};

bool IsNumber(char* string);
std::optional<int64_t> StringToUint(char* string);
Arguments ArgsReading(int argc, char** argv);
