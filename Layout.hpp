#ifndef LAYOUT_HPP_TINY_
#define LAYOUT_HPP_TINY_

#include <ncurses.h>		// for win

#include "Framework.hpp"	// for inheritance

class Layout : public Framework {
	friend class Scene;

private:
	Layout();
	Layout(const Layout& rhs) = delete;
	virtual ~Layout();

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;
	virtual void setColor(int fg, int bg) override;

	virtual void update() override;
	virtual void render() override;

private:
	WINDOW *win;
};

#endif
