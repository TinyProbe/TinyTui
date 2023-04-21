#include "Terminal.hpp"		// for declare class
#include <ncurses.h>		// for many many things

Terminal *Terminal::instance = nullptr;
Terminal& Terminal::getInstance() {
	if (Terminal::instance == nullptr) {
		Terminal::instance = new Terminal();
	}
	return *Terminal::instance;
}

void Terminal::addScene(SceneId sid) {
	if (scenes.find(sid) != scenes.end())
		throw std::runtime_error("already exist that scene.");
	scenes[sid];
}
void Terminal::delScene(SceneId sid) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	if (focus == sid)
		throw std::runtime_error("the focused scene cannot be removed.");
	scenes.erase(iter);
}
void Terminal::setSceneSize(SceneId sid, size_t row, size_t col) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	iter->second.setSize(row, col);
	if (sid == focus)
		setSize(row, col);
}
void Terminal::setSceneAxis(SceneId sid, int y, int x) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	iter->second.setAxis(y, x);
	if (sid == focus)
		setAxis(y, x);
}
void Terminal::setFocus(SceneId sid) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	focus = sid;
	setSize(iter->second.getRow(), iter->second.getCol());
	setAxis(iter->second.getY(), iter->second.getX());
}

void Terminal::addLayer(SceneId sid, LayerId lid) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	iter->second.addLayer(lid);
}
void Terminal::delLayer(SceneId sid, LayerId lid) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	iter->second.delLayer(lid);
}
void Terminal::setLayerSize(SceneId sid, LayerId lid, size_t row, size_t col) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	iter->second.setLayerSize(lid, row, col);
}
void Terminal::setLayerAxis(SceneId sid, LayerId lid, int y, int x) {
	std::unordered_map<SceneId, Scene>::iterator iter = scenes.find(sid);
	if (iter == scenes.end())
		throw std::runtime_error("doesn't exist that scene.");
	iter->second.setLayerAxis(lid, y, x);
}

void Terminal::update() {
	if (focus == -1)
		throw std::runtime_error("not focused any scene.");
	scenes[focus].update();
}
void Terminal::render() {
	if (focus == -1)
		throw std::runtime_error("not focused any scene.");
	scenes[focus].render();
}

Terminal::Terminal() :
	Framework(),
	focus(-1)
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
	Framework::setSize(row, col);
	size_refresh();
}
void Terminal::setAxis(int y, int x) {
	Framework::setAxis(y, x);
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
