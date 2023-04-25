#include "Layout.hpp"		// for declare class

Layout::Layout() :
	Framework(),
	win(newwin(0, 0, 0, 0))
{}
Layout::~Layout() {}

void Layout::setSize(size_t row, size_t col) {
	Framework::setSize(row, col);
	if (wresize(win, row, col) == ERR)
		throw std::runtime_error("layout area cannot be over range that its included scene.");
}
void Layout::setAxis(int y, int x) {
	Framework::setAxis(y, x);
	if (wmove(win, y, x) == ERR)
		throw std::runtime_error("layout area cannot be over range that its included scene.");
}
void Layout::setColor(int fg, int bg) {
	Framework::setColor(fg, bg);
	wattron(win, CLRPR(fg, bg));
}

void Layout::update() {}
void Layout::render() {}
