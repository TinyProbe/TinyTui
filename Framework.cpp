#include "Framework.hpp"

Framework::Framework() :
	row(),
	col(),
	y(),
	x()
{}
Framework::~Framework() {}

size_t Framework::getRow() const { return row; }
size_t Framework::getCol() const { return col; }
int Framework::getY() const { return y; }
int Framework::getX() const { return x; }

void Framework::setSize(size_t row, size_t col) {
	this->row = row;
	this->col = col;
}
void Framework::setAxis(int y, int x) {
	this->y = y;
	this->x = x;
}
