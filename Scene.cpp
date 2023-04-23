#include "Scene.hpp"		// for declare class
#include <utility>			// for pair

Scene::Scene() :
	Framework(),
	win(newwin(0, 0, 0, 0))
{}
Scene::~Scene() {
	delwin(win);
}

void Scene::addLayout(LayoutId lid) {
	validation(lid, false);
	layouts[lid];
}
void Scene::delLayout(LayoutId lid) {
	layouts.erase(validation(lid, true));
}
void Scene::setLayoutSize(LayoutId lid, size_t row, size_t col) {
	validation(lid, true)->second.setSize(row, col);
}
void Scene::setLayoutAxis(LayoutId lid, int y, int x) {
	validation(lid, true)->second.setAxis(y, x);
}
void Scene::setLayoutColor(LayoutId lid, int fg, int bg) {
	validation(lid, true)->second.setColor(fg, bg);
}

void Scene::setSize(size_t row, size_t col) {
	Framework::setSize(row, col);
	wresize(win, row, col);
}
void Scene::setAxis(int y, int x) {
	Framework::setAxis(y, x);
}
void Scene::setColor(int fg, int bg) {
	Framework::setColor(fg, bg);
	wattron(win, CLRPR(fg, bg));
}

void Scene::update() {
	for (auto& e : layouts)
		e.second.update();
}
void Scene::render() {
	for (auto& e : layouts)
		e.second.render();
// 	std::priority_queue<std::pair<Priority, LayoutId>> order;
// 	for (auto& e : layouts)
// 		order.push(std::pair<Priority, layoutId>({ e.second.prior, e.first }));
// 	while (order.size()) {
// 		std::pair<Priority, layoutId> next = order.top(); order.pop();
// 		layouts[next.second].render();
// 	}
}

std::unodered_map<LayoutId, Layout>::iterator Scene::validation(LayoutId lid, bool exist) {
	std::unodered_map<LayoutId, Layout>::iterator iter = layouts.find(lid);
	if ((iter != layouts.end()) != exist)
		throw std::runtime_error(exist ? "doesn't exist that layout." : "already exist that layout.");
	return iter;
}
