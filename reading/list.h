#include <iostream>
#include "field/point.h"

struct Cell {
	Point value = Point(0, 0, 0);
	Cell* next = nullptr;
};

class List {
	private:
		Cell* head = nullptr;
	public:
		void Append(const Point& new_point);
		Point Front() const;
		void Pop();
		bool IsEnd() const;
		void print();
};

