#ifndef LAYER_HPP_TINY_
#define LAYER_HPP_TINY_

#include <ncurses.h>

#include "Framework.hpp"

using Layerid = WINDOW *;

class Scene;
class Layer : public Framework {
public:

private:
	Layer() = delete;
	Layer(const Layer& rhs) = delete;
	Layer(Scene *dependence);
	virtual ~Layer();

	virtual void setRow(size_t row) override;
	virtual void setCol(size_t col) override;
	virtual void setY(int y) override;
	virtual void setX(int x) override;

	virtual void update() override;
	virtual void render() override;

private:
	Scene *dependence;
	Layerid id;

	friend class Scene;
};

#endif
