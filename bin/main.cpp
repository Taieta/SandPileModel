#include <iostream>
#include "reading/args_reading.h"
#include "field/field.h"
#include "drawing/image.h"
#include "field/sandpile.h"
#include "reading/tsv_reading.h"

int main(int argc, char** argv) {
	Arguments user_input = ArgsReading(argc, argv);

	if (user_input.is_error) {
		std::cerr << "error occured\n";
		return EXIT_FAILURE;
	}

	auto NotFinished = [&](uint64_t cur_iter, uint64_t max_iter, Sandpile new_pile) ->  bool {return max_iter == 0 ? !new_pile.IsCompleted() : cur_iter < max_iter;};
	auto NeedToImage = [&](uint64_t freq, uint64_t cur_iter) -> bool {return freq == 0 ? false : cur_iter % freq == 0;};

	Field start_coordinates = std::move(ParseTSV(user_input.input));
	Sandpile new_pile(start_coordinates);
	uint64_t cur_iter = 0;
	while (NotFinished(cur_iter, user_input.max_iter, new_pile)) {
		new_pile.Iteration();
		++cur_iter;
		if (NeedToImage(user_input.freq, cur_iter)) {
			new_pile.Cutting();
			ToImage(new_pile.field, user_input, cur_iter);
		}
	}

	new_pile.Cutting();
	ToImage(new_pile.field, user_input, cur_iter);
	std::cout << "File created!\n";

	return EXIT_SUCCESS;
}
