#include "layout.hpp"		// for declare class

layout::layout() :
	Framework(),
	win()
{}
layout::~layout() {}

void layout::setSize(size_t row, size_t col) {
	Framework::setSize(row, col);
	if (wresize(win, row, col) == ERR)
		throw std::runtime_error("layout area cannot be over range that its included scene.");
}
void layout::setAxis(int y, int x) {
	Framework::setAxis(y, x);
	if (wmove(win, y, x) == ERR)
		throw std::runtime_error("layout area cannot be over range that its included scene.");
}
void setColor(int fg, int bg) override {
	Framework::setColor(fg, bg);
	wattron(win, CLRPR(fg, bg));
}

void layout::update() {}
void layout::render() {}
