#include "Button.hpp"

Button::Button() :
	Object(),
	border(),
	render_border()
{}
Button::~Button() {}

const Border& Button::getBorder() const { return border; }
bool Button::getRenderBorder() const { return render_border; }

void Button::setBorder(const Border& border) { this->border = border; }
void Button::setRenderBorder(bool render_border) { this->render_border = render_border; }

void Button::update() {}
void Button::render() {}
