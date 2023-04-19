#include "Layer.hpp"
#include "Scene.hpp"

Layer::Layer(Scene *dependence) :
	Framework(),
	dependence(dependence),
	id(subwin(dependence->getID(), 0, 0, 0, 0))
{}
Layer::~Layer() {}

void Layer::setRow(size_t row) {

}
void Layer::setCol(size_t col) {

}
void Layer::setY(int y) {

}
void Layer::setX(int x) {

}

void Layer::update() {}
void Layer::render() {}
