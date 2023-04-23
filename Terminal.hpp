#ifndef TERMINAL_HPP_TINY_
#define TERMINAL_HPP_TINY_

#include <unordered_map>	// for scenes
#include <queue>			// for frame_time
#include <chrono>			// for frame_time

#include "Scene.hpp"		// for scenes

using SceneId = unsigned int;

class Terminal {
public:
	static Terminal& getInstance();

	virtual void addScene(SceneId sid);
	virtual void delScene(SceneId sid);
	virtual void setSceneSize(SceneId sid, size_t row, size_t col);
	virtual void setSceneAxis(SceneId sid, int y, int x);
	virtual void setSceneColor(SceneId sid, int fg, int bg);

	virtual void addLayout(SceneId sid, LayoutId lid);
	virtual void delLayout(SceneId sid, LayoutId lid);
	virtual void setLayoutSize(SceneId sid, LayoutId lid, size_t row, size_t col);
	virtual void setLayoutAxis(SceneId sid, LayoutId lid, int y, int x);
	virtual void setLayoutColor(SceneId sid, LayoutId lid, int fg, int bg);

	virtual int getCurrKey() const;
	virtual const std::chrono::time_point<std::chrono::steady_clock>& getCurrTime() const;
	virtual const std::chrono::time_point<std::chrono::steady_clock>& getPrevTime() const;

	virtual void setFocus(SceneId sid);
	virtual void setFpsLimit(size_t fps_limit);
	virtual void setRenderFps(bool render_fps);

	virtual void run_framework();

private:
	Terminal();
	Terminal(const Terminal& rhs) = delete;
	virtual ~Terminal();

	virtual int getNextKey();

	static void refreshSize(size_t row, size_t col);
	static void refreshAxis(int y, int x);
	static std::unodered_map<SceneId, Scene>::iterator validation(SceneId sid, bool exist);

private:
	static Terminal *instance;
	int key;

	std::unordered_map<SceneId, Scene> scenes;
	SceneId focus;
	std::queue<std::chrono::time_point<std::chrono::steady_clock>> frame_time;
	size_t fps_limit;
	bool render_fps;
};

#endif
