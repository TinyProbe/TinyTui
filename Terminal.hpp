#ifndef TERMINAL_HPP_TINY_
#define TERMINAL_HPP_TINY_

#include <unordered_map>	// for scenes
#include <string>			// for name

#include "Framework.hpp"	// for inheritance
#include "Scene.hpp"		// for scenes

class Terminal : public Framework {
public:
	static Terminal& getInstance();

	virtual void addScene(const std::string& name);
	virtual void delScene(const std::string& name);
	virtual void setSceneSize(const std::string& name, size_t row, size_t col);
	virtual void setSceneAxis(const std::string& name, int y, int x);
	virtual void setFocus(const std::string& name);

	virtual void update() override;
	virtual void render() override;

private:
	Terminal();
	virtual ~Terminal();

	virtual void setSize(size_t row, size_t col) override;
	virtual void setAxis(int y, int x) override;

	virtual void refreshSize() const;
	virtual void refreshAxis() const;

private:
	static Terminal *instance;

	std::unordered_map<std::string, Scene> scenes;
	Scene* focus;
};

#endif
