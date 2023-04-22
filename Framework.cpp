#include "Framework.hpp"	// for declare class

int __current_key;

Framework::Framework() :
	row(),
	col(),
	y(),
	x(),
	fg(COLOR_WHITE),
	bg(COLOR_BLACK)
{}
Framework::~Framework() {}

size_t Framework::getRow() const { return row; }
size_t Framework::getCol() const { return col; }
int Framework::getY() const { return y; }
int Framework::getX() const { return x; }
int Framework::getFgColor() const { return fg; }
int Framework::getBgColor() const { return bg; }

void Framework::setSize(size_t row, size_t col) {
	this->row = row;
	this->col = col;
}
void Framework::setAxis(int y, int x) {
	this->y = y;
	this->x = x;
}
void setColor(int fg, int bg) {
	this->fg = fg;
	this->bg = bg;
}
