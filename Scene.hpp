#ifndef SCENE_HPP_TINY_
#define SCENE_HPP_TINY_

#include <ncurses.h>		// for win
#include <unordered_map>	// for layers

#include "Framework.hpp"	// for inheritance

using LayerId = unsigned int;
using Priority = unsigned int;

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
	virtual void setLayerColor(LayerId lid, int fg, int bg);

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;
	virtual void setColor(int fg, int bg) override;

	virtual void update() override;
	virtual void render() override;

	static std::unodered_map<LayerId, Layer>::iterator validation(LayerId lid, bool exist);

private:
	WINDOW *win;
	std::unordered_map<LayerId, Layer> layers;
};

#endif
