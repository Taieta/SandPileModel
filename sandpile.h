#include "field.h"

const uint8_t black_code = 4;

class Sandpile {
private:
	bool IsRightExpansion();
	bool IsLeftExpansion();
	bool IsUpExpansion();
	bool IsDownExpansion();
	void SandMove();
public:
	Field& field;
	Sandpile(Field& field): field(field) {};
	bool IsCompleted();
	void Iteration();
	void Cutting();
};
