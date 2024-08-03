#include "list.h"

void List::Append(const Point& new_point) {
	Cell* new_cell = new Cell;
	new_cell->next = head;
	new_cell->value = new_point;
	head = new_cell;
	return;
}

Point List::Front() const { return head->value; }

void List::Pop() {
	Cell* order = head;
	head = order->next;
	delete[] order;
	return;
}

bool List::IsEnd() const {
	return head == nullptr;
}

void List::print() {
	Cell* order = head;
	while (order != nullptr) {
		std::cout << order->value.x << ' ' << order->value.y << ' ' << order->value.n_grains << '\n';
		order = order->next;
	}
}

