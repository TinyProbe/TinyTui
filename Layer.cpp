#include "Layer.hpp"
#include "Scene.hpp"

Layer::Layer() :
	Framework(),
	win(),
	Prior()
{}
Layer::~Layer() {}

Prior Layer::getPriority() const {
	return prior;
}
void Layer::setPriority(Prior prior) {
	this->prior = prior;
}

void Layer::setSize(size_t row, size_t col) {
	Framework::setSize(row, col);
	wresize(win, row, col);
}
void Layer::setAxis(int y, int x) {
	Framework::setAxis(y, x);
	wmove(win, y, x);
}

void Layer::update() {

}
void Layer::render(std::vector<std::string>& buffer) {

}
