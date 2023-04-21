#ifndef TERMINAL_HPP_TINY_
#define TERMINAL_HPP_TINY_

#include <unordered_map>	// for scenes

#include "Framework.hpp"	// for inheritance
#include "Scene.hpp"		// for scenes

using SceneId = unsigned int;

class Terminal : public Framework {
public:
	static Terminal& getInstance();

	virtual void addScene(SceneId sid);
	virtual void delScene(SceneId sid);
	virtual void setSceneSize(SceneId sid, size_t row, size_t col);
	virtual void setSceneAxis(SceneId sid, int y, int x);

	virtual void setFocus(SceneId sid);

	virtual void addLayer(SceneId sid, LayerId lid);
	virtual void delLayer(LayerId sid, LayerId lid);
	virtual void setLayerSize(SceneId sid, LayerId lid, size_t row, size_t col);
	virtual void setLayerAxis(SceneId sid, LayerId lid, int y, int x);

	virtual void update() override;
	virtual void render() override;

private:
	Terminal();
	Terminal(const Terminal& rhs) = delete;
	virtual ~Terminal();

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;
	virtual void refreshSize() const;
	virtual void refreshAxis() const;

private:
	static Terminal *instance;

	std::unordered_map<SceneId, Scene> scenes;
	SceneId focus;
};

#endif
