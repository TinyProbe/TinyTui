#include "Terminal.hpp"		// for declare class
#include "Framework.hpp"	// for macro functions
#include <ncurses.h>		// for many many things
#include <string>			// for to_string

Terminal *Terminal::instance = nullptr;

Terminal& Terminal::getInstance() {
	if (Terminal::instance == nullptr) {
		Terminal::instance = new Terminal();
	}
	return *Terminal::instance;
}

void Terminal::addScene(SceneId sid) {
	validation(sid, false);
	scenes[sid];
}
void Terminal::delScene(SceneId sid) {
	if (focus == sid)
		throw std::runtime_error("the focused scene cannot be removed.");
	scenes.erase(validation(sid, true));
}
void Terminal::setSceneSize(SceneId sid, size_t row, size_t col) {
	validation(sid, true)->second.setSize(row, col);
	if (sid == focus)
		refreshSize(row, col);
}
void Terminal::setSceneAxis(SceneId sid, int y, int x) {
	validation(sid, true)->second.setAxis(y, x);
	if (sid == focus)
		refreshAxis(y, x);
}
void Terminal::setSceneColor(SceneId sid, int fg, int bg) {
	validation(sid, true)->second.setColor(fg, bg);
}

void Terminal::addLayer(SceneId sid, LayerId lid) {
	validation(sid, true)->second.addLayer(lid);
}
void Terminal::delLayer(SceneId sid, LayerId lid) {
	validation(sid, true)->second.delLayer(lid);
}
void Terminal::setLayerSize(SceneId sid, LayerId lid, size_t row, size_t col) {
	validation(sid, true)->second.setLayerSize(lid, row, col);
}
void Terminal::setLayerAxis(SceneId sid, LayerId lid, int y, int x) {
	validation(sid, true)->second.setLayerAxis(lid, y, x);
}
void Terminal::setLayerColor(SceneId sid, LayerId lid, int fg, int bg) {
	validation(sid, true)->second.setLayerColor(lid, fg, bg);
}

void Terminal::setFocus(SceneId sid) {
	std::unodered_map<SceneId, Scene>::iterator iter = validation(sid, true);
	focus = sid;
	refreshSize(iter->second.getRow(), iter->second.getCol());
	refreshAxis(iter->second.getY(), iter->second.getX());
}
void Terminal::setFpsLimit(size_t fps) {
	this->fps = fps;
}
void setRenderFps(bool is_render_fps) {
	this->is_render_fps = is_render_fps;
}

void Terminal::run_framework() {
	if (focus == -1)
		throw std::runtime_error("not focused any scene.");
	while ((__current_key = getch()) != 'q') {
		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		while (frame_time.size() && std::chrono::duration_cast<milliseconds>(now - frame_time.front()).count() >= 1000)
			frame_time.pop();
		if (frame_time.size() < fps) {
			frame_time.push(now);
			std::unodered_map<SceneId, Scene>::iterator iter = scenes.find(focus);
			iter->second.update(now); // Scene class update method need remind
			iter->second.render();
			if (is_render_fps)
				mvwprintw(iter->second.win, 0, 0, "%s", to_string(frame_time.size()).c_str());
		}
	}
}

Terminal::Terminal() :
	Framework(),
	focus(-1),
	fps(30)
{
	initscr();
	timeout(0);
	curs_set(0);
	noecho();
	cbreak();
	nonl();
	for (int i = 0; i < COLOR_MAX; ++i) {
		for (int j = 0; j < COLOR_MAX; ++j) {
			init_pair(CLRIX(i, j), i, j);
		}
	}
}
Terminal::~Terminal() {
	if (Terminal::instance) {
		delete Terminal::instance;
		Terminal::instance = nullptr;
	}
	endwin();
}

void Terminal::refreshSize(size_t row, size_t col) const {
	std::string cmd = "printf '\e[8;";
	cmd += std::to_string(row) + ';';
	cmd += std::to_string(col) + "t'";
	system(cmd.c_str());
}
void Terminal::refreshAxis(int y, int x) const {
	std::string cmd = "printf '\e[3;";
	cmd += std::to_string(x) + ';';
	cmd += std::to_string(y) + "t'";
	system(cmd.c_str());
}
std::unodered_map<SceneId, Scene>::iterator Terminal::validation(SceneId sid, bool exist) {
	std::unodered_map<SceneId, Scene>::iterator iter = Scenes.find(sid);
	if ((iter != scenes.end()) != exist)
		throw std::runtime_error(exist ? "doesn't exist that scene." : "already exist that scene.");
	return iter;
}
