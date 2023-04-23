#ifndef LAYOUT_HPP_TINY_
#define LAYOUT_HPP_TINY_

#include <ncurses.h>		// for win

#include "Framework.hpp"	// for inheritance

class layout : public Framework {
	friend class Scene;

private:
	layout();
	layout(const layout& rhs) = delete;
	virtual ~layout();

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;
	virtual void setColor(int fg, int bg) override;

	virtual void update() override;
	virtual void render() override;

private:
	WINDOW *win;
};

#endif
