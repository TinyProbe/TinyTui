#ifndef OBJECT_HPP_TINY_
#define OBJECT_HPP_TINY_

#include "Framework.hpp"		// for inheritance

class Object : public Framework {
protected:
	Object();
	Object(const Object& rhs) = delete;
	~Object();

	virtual size_t getRow() const;
	virtual size_t getCol() const;
	virtual int getY() const;
	virtual int getX() const;
	virtual int getFgColor() const;
	virtual int getBgColor() const;

	virtual void setSize(size_t row, size_t col);
	virtual void setAxis(int y, int x);
	virtual void setColor(int fg, int bg);

	virtual void update() = 0;
	virtual void render() = 0;

private:
	size_t row, col;
	int y, x;
	int fg, bg;
};

#endif
