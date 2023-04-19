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

void Framework::setRow(size_t row) { this->row = row; }
void Framework::setCol(size_t col) { this->col = col; }
void Framework::setY(int y) { this->y = y; }
void Framework::setX(int x) { this->x = x; }
