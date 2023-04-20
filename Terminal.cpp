#include "Terminal.hpp"		// for declaration
#include <ncurses.h>		// for many many things

Terminal *Terminal::instance = nullptr;

Terminal& Terminal::getInstance() {
	if (Terminal::instance == nullptr) {
		Terminal::instance = new Terminal();
	}
	return *Terminal::instance;
}

void addScene(const std::string& name) {
	if (scenes.find(name) != scenes.end())
		throw std::runtime_error("already exist that scene.");
	scenes[name];
}
void delScene(const std::string& name) {
	if (scenes.find(name) == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	scenes.erase(name);
}
void setSceneSize(const std::string& name, size_t row, size_t col) {
	if (scenes.find(name) == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	scenes[name].setSize(row, col);
}
void setSceneAxis(const std::string& name, int y, int x) {
	if (scenes.find(name) == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	scenes[name].setAxis(y, x);
}
void setFocus(const std::string& name) {
	if (scenes.find(name) == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	focus = &scenes[name];
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

Terminal::Terminal() :
	Framework(),
	focus()
{
	initscr();
	timeout(0);
	curs_set(0);
	noecho();
	cbreak();
	nonl();
}

Terminal::~Terminal() {
	if (Terminal::instance) {
		delete Terminal::instance;
		Terminal::instance = nullptr;
	}
	endwin();
}

void Terminal::setSize(size_t row, size_t col) {
	Framework::setRow(row);
	Framework::setCol(col);
	size_refresh();
}
void Terminal::setAxis(int y, int x) {
	Framework::setY(y);
	Framework::setX(x);
	axis_refresh();
}

void Terminal::refreshSize() const {
	std::string cmd = "printf '\e[8;";
	cmd += std::to_string(getRow()) + ';';
	cmd += std::to_string(getCol()) + "t'";
	system(cmd.c_str());
}
void Terminal::refreshAxis() const {
	std::string cmd = "printf '\e[3;";
	cmd += std::to_string(getX()) + ';';
	cmd += std::to_string(getY()) + "t'";
	system(cmd.c_str());
}
