#include "args_reading.h"

bool IsNumber(char* string) {
	for (int i = 0; i < strlen(string); ++i) {
		if (!(std::isdigit(string[i]))) {
			return false;
		}
	}
	return true;
}

std::optional<int64_t> StringToUint(char* string) {
	if (!IsNumber(string)) return std::nullopt;
	return std::strtoll(string, 0, 10);
}

Arguments ArgsReading(int argc, char** argv) {
	Arguments user_input;
	for (int i = 0; i < argc; ++i) {
		char* current_input = argv[i];

		if (!(strcmp(current_input, "-i"))) {
			if (i + 1 >= argc) {
				std::cerr << "incorrect input" << '\n';
				user_input.is_error = true;
				break;
			}
			user_input.input = argv[i + 1];
			++i;
		} else if (!(strncmp(current_input, "--input=", 8))) {
			char* next_arg = current_input + 8;
			user_input.input = next_arg;
		} else if (!(strcmp(current_input, "-o"))) {
			if (i + 1 >= argc) {
				std::cerr << "incorrect input" << '\n';
				user_input.is_error = true;
				break;
			}
			char* next_arg = argv[i + 1];
			user_input.path = next_arg;
			++i;
		} else if (!(strncmp(current_input, "--output=", 9))) {
			char* next_arg = current_input + 9;
			user_input.path = next_arg;
		} else if (!(strcmp(current_input, "-m"))) {
			if (i + 1 >= argc) {
				std::cerr << "incorrect input" << '\n';
				user_input.is_error = true;
				break;
			}
			char* next_arg = argv[i + 1];
			if (!StringToUint(next_arg).has_value()) {
				std::cerr << "incorrect max iteration value" << '\n';
				user_input.is_error = true;
				break;
			}
			user_input.max_iter = StringToUint(next_arg).value();
			++i;
		} else if (!(strncmp(current_input, "--max-iter=", 11))) {
			char* next_arg = current_input + 11;
			if (!StringToUint(next_arg).has_value()) {
				std::cerr << "incorrect max iteration value" << '\n';
				user_input.is_error = true;
				break;
			}
			user_input.max_iter = StringToUint(next_arg).value();
		} else if (!(strcmp(current_input, "-f"))) {
			if (i + 1 >= argc) {
				std::cerr << "incorrect input" << '\n';
				user_input.is_error = true;
				break;
			}
			char* next_arg = argv[i + 1];
			if (!StringToUint(next_arg).has_value()) {
				std::cerr << "incorrect frequency value" << '\n';
				user_input.is_error = true;
				break;
			}
			user_input.freq = StringToUint(next_arg).value();
			++i;
		} else if (!(strncmp(current_input, "--freq", 7))) {
			char* next_arg = current_input + 7;
			if (!StringToUint(next_arg).has_value()) {
				std::cerr << "incorrect frequency value" << '\n';
				user_input.is_error = true;
				break;
			}
			user_input.freq = StringToUint(next_arg).value();
		}
	}

	return user_input;
}
