#ifndef SCENE_HPP_TINY_
#define SCENE_HPP_TINY_

#include <ncurses.h>		// for win
#include <vector>			// for buffer
#include <string>			// for buffer
#include <unordered_map>	// for layers

#include "Framework.hpp"	// for inheritance

using LayerId = unsigned int;

class Scene : public Framework {
	friend class Terminal;

private:
	Scene();
	Scene(const Scene& rhs) = delete;
	virtual ~Scene();

	virtual void addLayer(LayerId lid);
	virtual void delLayer(LayerId lid);
	virtual void setLayerSize(LayerId lid, size_t row, size_t col);
	virtual void setLayerAxis(LayerId lid, int y, int x);
	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;

	virtual void update() override;
	virtual void render() override;

private:
	WINDOW *win;
	std::vector<std::string> buffer;
	std::unordered_map<LayerId, Layer> layers;
};

#endif
