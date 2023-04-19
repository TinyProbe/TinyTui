#ifndef TERMINAL_HPP_TINY_
#define TERMINAL_HPP_TINY_

#include <unordered_map>
#include <string>

#include "Framework.hpp"
#include "Scene.hpp"

class Terminal : public Framework {
public:
	static Terminal& get();

	virtual Scene* getFocus() const;
	virtual void setFocus(const std::string& name);

	virtual void addScene(const std::string& name, size_t row, size_t col, int y, int x);
	virtual void delScene(const std::string& name);

	virtual void update() override;
	virtual void render() override;

private:
	Terminal();
	virtual ~Terminal();

	virtual void setRow(size_t row) override;
	virtual void setCol(size_t col) override;
	virtual void setY(int y) override;
	virtual void setX(int x) override;

	virtual void size_refresh() const;
	virtual void axis_refresh() const;

private:
	static Terminal *instance;

	std::unordered_map<std::string, Scene> scenes;
	Scene* focus;
};

#endif
