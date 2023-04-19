#include "Terminal.hpp"
#include <ncurses.h>

Terminal *Terminal::instance = nullptr;
Terminal& Terminal::get() {
	if (Terminal::instance == nullptr) {
		Terminal::instance = new Terminal();
	}
	return *Terminal::instance;
}

Terminal::Terminal() :
	Framework(),
	focus()
{
	initscr();
	curs_set(0);
	noecho();
	cbreak();
}
Terminal::~Terminal() {
	if (Terminal::instance) {
		delete Terminal::instance;
		Terminal::instance = nullptr;
	}
	endwin();
}

Scene *Terminal::getFocus() const { return focus; }

void Terminal::setFocus(const std::string& name) {
	std::unordered_map<std::string, Scene>::iterator iter = scenes.find(name);
	if (iter == scenes.end())
		throw std::runtime_error("not exist scene like that.");
	this->focus = &(iter->second);
}

void Terminal::addScene(const std::string& name, size_t row, size_t col, int y, int x) {

}
void Terminal::delScene(const std::string& name) {

}

void Terminal::update() {
	if (focus == nullptr)
		throw std::runtime_error("not focused any scene.");
	focus->update();
}
void Terminal::render() {
	if (focus == nullptr)
		throw std::runtime_error("not focused any scene.");
	focus->render();
}

void Terminal::setRow(size_t row) { setRow(row), size_refresh(); }
void Terminal::setCol(size_t col) { setCol(col), size_refresh(); }
void Terminal::setY(int y) { setY(y), axis_refresh(); }
void Terminal::setX(int x) { setX(x), axis_refresh(); }

void Terminal::size_refresh() const {
	std::string cmd = "printf '\e[8;";
	cmd += std::to_string(getRow()) + ';';
	cmd += std::to_string(getCol()) + "t'";
	system(cmd.c_str());
}
void Terminal::axis_refresh() const {
	std::string cmd = "printf '\e[3;";
	cmd += std::to_string(getX()) + ';';
	cmd += std::to_string(getY()) + "t'";
	system(cmd.c_str());
}
