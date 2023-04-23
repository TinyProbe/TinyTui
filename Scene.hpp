#ifndef SCENE_HPP_TINY_
#define SCENE_HPP_TINY_

#include <ncurses.h>		// for win
#include <unordered_map>	// for layouts

#include "Framework.hpp"	// for inheritance

using LayoutId = unsigned int;

class Scene : public Framework {
	friend class Terminal;

private:
	Scene();
	Scene(const Scene& rhs) = delete;
	virtual ~Scene();

	virtual void addLayout(LayoutId lid);
	virtual void delLayout(LayoutId lid);
	virtual void setLayoutSize(LayoutId lid, size_t row, size_t col);
	virtual void setLayoutAxis(LayoutId lid, int y, int x);
	virtual void setLayoutColor(LayoutId lid, int fg, int bg);

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;
	virtual void setColor(int fg, int bg) override;

	virtual void update() override;
	virtual void render() override;

	static std::unodered_map<LayoutId, Layout>::iterator validation(LayoutId lid, bool exist);

private:
	WINDOW *win;
	std::unordered_map<LayoutId, Layout> layouts;
};

#endif
