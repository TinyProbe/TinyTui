#include "Scene.hpp"		// for declare class
#include <utility>			// for pair

Scene::Scene() :
	Framework(),
	win(newwin(0, 0, 0, 0))
{}
Scene::~Scene() {
	delwin(win);
}

void Scene::addLayer(LayerId lid) {
	validation(lid, false);
	layers[lid];
}
void Scene::delLayer(LayerId lid) {
	layers.erase(validation(lid, true));
}
void Scene::setLayerSize(LayerId lid, size_t row, size_t col) {
	validation(lid, true)->second.setSize(row, col);
}
void Scene::setLayerAxis(LayerId lid, int y, int x) {
	validation(lid, true)->second.setAxis(y, x);
}
void Scene::setLayerColor(LayerId lid, int fg, int bg) {
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
}

void Scene::update() {
	for (auto& e : layers)
		e.second.update();
}
void Scene::render() {
	std::priority_queue<std::pair<Priority, LayerId>> order;
	for (auto& e : layers)
		order.push(std::pair<Priority, LayerId>({ e.second.prior, e.first }));
	while (order.size()) {
		std::pair<Priority, LayerId> next = order.top(); order.pop();
		layers[next.second].render();
	}
}

std::unodered_map<LayerId, Layer>::iterator Scene::validation(LayerId lid, bool exist) {
	std::unodered_map<LayerId, Layer>::iterator iter = Layers.find(lid);
	if ((iter != layers.end()) != exist)
		throw std::runtime_error(exist ? "doesn't exist that layer." : "already exist that layer.");
	return iter;
}
