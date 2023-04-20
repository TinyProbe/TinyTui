#include "Scene.hpp"

Scene::Scene() :
	Framework(),
	id(newwin(0, 0, 0, 0))
{}
Scene::~Scene() {}

Sceneid Scene::getID() const { return id; }

void Scene::setRow(size_t row) {}
void Scene::setCol(size_t col) {}
void Scene::setY(int y) {}
void Scene::setX(int x) {}

void Scene::update() {}
void Scene::render() {}
