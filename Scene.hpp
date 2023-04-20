#ifndef SCENE_HPP_TINY_
#define SCENE_HPP_TINY_

#include <ncurses.h>

#include "Framework.hpp"

using Sceneid = WINDOW *;

class Scene : public Framework {
	friend class Terminal;

private:
	Scene();
	virtual ~Scene();

	virtual Sceneid getID() const;

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;

	virtual void update() override;
	virtual void render() override;

private:
	static constexpr size_t MAX_ROW = 1024;
	static constexpr size_t MAX_COL = 2048;
	static constexpr size_t MAX_Y = 5000;
	static constexpr size_t MAX_X = 5000;

	Sceneid id;
};

#endif
