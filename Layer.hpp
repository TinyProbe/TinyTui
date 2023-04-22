#ifndef LAYER_HPP_TINY_
#define LAYER_HPP_TINY_

#include <ncurses.h>		// for id
#include <vector>			// for buffer
#include <string>			// for buffer

#include "Framework.hpp"	// for inheritance

using Priority = unsigned int;

class Layer : public Framework {
	friend class Scene;

private:
	Layer();
	Layer(const Layer& rhs) = delete;
	virtual ~Layer();

	virtual Prior getPriority() const;

	virtual void setPriority(Prior prior);
	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;

	virtual void update() override;
	virtual void render(std::vector<std::string>& buffer) override;

private:
	WINDOW *win;
	Priority prior;
};

#endif
