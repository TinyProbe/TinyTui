#include "Object.hpp"		// for declare class

Object::Object() {}
Object::~Object() {}

size_t Object::getRow() const { return row; }
size_t Object::getCol() const { return col; }
int Object::getY() const { return y; }
int Object::getX() const { return x; }
int Object::getFgColor() const { return fg; }
int Object::getBgColor() const { return bg; }

void Object::setSize(size_t row, size_t col) { this->row = row, this->col = col; }
void Object::setAxis(int y, int x) { this->y = y, this->x = x; }
void Object::setColor(int fg, int bg) { this->fg = fg, this->bg = bg; }
