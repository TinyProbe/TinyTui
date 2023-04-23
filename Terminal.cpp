#include "Terminal.hpp"		// for declare class
#include "Framework.hpp"	// for macro functions
#include <ncurses.h>		// for many many things
#include <string>			// for to_string

Terminal *Terminal::instance = nullptr;

Terminal& Terminal::getInstance() {
	if (Terminal::instance == nullptr)
		Terminal::instance = new Terminal();
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

void Terminal::addlayout(SceneId sid, layoutId lid) {
	validation(sid, true)->second.addlayout(lid);
}
void Terminal::dellayout(SceneId sid, layoutId lid) {
	validation(sid, true)->second.dellayout(lid);
}
void Terminal::setlayoutSize(SceneId sid, layoutId lid, size_t row, size_t col) {
	validation(sid, true)->second.setlayoutSize(lid, row, col);
}
void Terminal::setlayoutAxis(SceneId sid, layoutId lid, int y, int x) {
	validation(sid, true)->second.setlayoutAxis(lid, y, x);
}
void Terminal::setlayoutColor(SceneId sid, layoutId lid, int fg, int bg) {
	validation(sid, true)->second.setlayoutColor(lid, fg, bg);
}

int Terminal::getCurrKey() const { return key; }
const std::chrono::time_point<std::chrono::steady_clock>& Terminal::getCurrTime() const {
	return (frame_time.size() > 0
		? frame_time.back()
		: std::chrono::time_point<std::chrono::steady_clock>());
}
const std::chrono::time_point<std::chrono::steady_clock>& Terminal::getPrevTime() const {
	return (frame_time.size() > 1
		? --frame_time.back()
		: std::chrono::time_point<std::chrono::steady_clock>());
}

void Terminal::setFocus(SceneId sid) {
	std::unodered_map<SceneId, Scene>::iterator iter = validation(sid, true);
	focus = sid;
	refreshSize(iter->second.getRow(), iter->second.getCol());
	refreshAxis(iter->second.getY(), iter->second.getX());
}
void Terminal::setFpsLimit(size_t fps_limit) {
	this->fps_limit = fps_limit;
}
void setRenderFps(bool render_fps) {
	this->render_fps = render_fps;
}

void Terminal::run_framework() {
	if (focus == ~0)
		throw std::runtime_error("not focused any scene.");
	while (true) {
		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		while (frame_time.size() && std::chrono::duration_cast<std::chrono::milliseconds>(now - frame_time.front()).count() >= 1000)
			frame_time.pop();
		if (frame_time.size() >= fps)
			continue;
		frame_time.push(now);
		if (getNextKey() == 'q')
			break;
		std::unodered_map<SceneId, Scene>::iterator iter = scenes.find(focus);
		iter->second.update(now);
		iter->second.render();
		if (render_fps)
			mvwprintw(iter->second.win, 0, 0, "%s", to_string(frame_time.size()).c_str());
	}
}

Terminal::Terminal() :
	Framework(),
	key(),
	focus(~0),
	fps(30)
{
	initscr();
	keypad(stdscr, TRUE);
	timeout(0);
	curs_set(0);
	noecho();
	cbreak();
	nonl();
	start_color();
	for (int i = 0; i < COLOR_MAX; ++i) {
		for (int j = 0; j < COLOR_MAX; ++j) {
			init_pair(CLRIX(i, j), i, j);
		}
	}
}
Terminal::~Terminal() {
	if (Terminal::instance)
		delete Terminal::instance;
	endwin();
}

int Terminal::getNextKey() { return (key = getch()); }

void Terminal::refreshSize(size_t row, size_t col) {
	std::string cmd = "printf '\e[8;";
	cmd += std::to_string(row) + ';';
	cmd += std::to_string(col) + "t'";
	system(cmd.c_str());
}
void Terminal::refreshAxis(int y, int x) {
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
