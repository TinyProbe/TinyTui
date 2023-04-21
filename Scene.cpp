#include "Scene.hpp"		// for declare class

Scene::Scene() :
	Framework(),
	win(newwin(0, 0, 0, 0))
{}
Scene::~Scene() {
	delwin(win);
}

void Scene::addLayer(LayerId lid) {
	if (layers.find(lid) != layers.end())
		throw std::runtime_error("already exist that layer.");
	layers[lid];
}
void Scene::delLayer(LayerId lid) {
	std::unodered_map<LayerId, Layer>::iterator iter = Layers.find(lid);
	if (iter == layers.end())
		throw std::runtime_error("doesn't exist that layer.");
	layers.erase(iter);
}
void setLayerSize(LayerId lid, size_t row, size_t col) {
	std::unodered_map<LayerId, Layer>::iterator iter = Layers.find(lid);
	if (iter == layers.end())
		throw std::runtime_error("doesn't exist that layer.");
	// next work in here ...
	iter->second.setSize(row, col);
}
void setLayerAxis(LayerId lid, int y, int x) {
	std::unodered_map<LayerId, Layer>::iterator iter = Layers.find(lid);
	if (iter == layers.end())
		throw std::runtime_error("doesn't exist that layer.");
	size_t row_space = getRow() - iter->second.getRow();
	size_t col_space = getCol() - iter->second.getCol();
	if () {} // check if axis can out of range of window of main if can, just push the value.
	iter->second.setAxis(y, x);
}
void Scene::setSize(size_t row, size_t col) {
	Framework::setSize(row, col);
	wresize(win, row, col);
	buffer.resize(row);
}
void Scene::setAxis(int y, int x) {
	Framework::setAxis(y, x);
}

void Scene::update() {
	for (auto& e : layers)
		e.second.update();
}
void Scene::render() {
	for (auto& e : buffer) {
		e.clear();
		e.resize(col, ' ');
	}
	std::priority_queue<std::pair<unsigned int, LayerId>> order;
	for (auto& e : layers)
		e.second.render(buffer);
}
