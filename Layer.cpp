#include "Layer.hpp"		// for declare class

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
	if (wresize(win, row, col) == ERR)
		throw std::runtime_error("layer area cannot be over range that its included scene.");
}
void Layer::setAxis(int y, int x) {
	Framework::setAxis(y, x);
	if (wmove(win, y, x) == ERR)
		throw std::runtime_error("layer area cannot be over range that its included scene.");
}

void Layer::update() {

}
void Layer::render(std::vector<std::string>& buffer) {

}
