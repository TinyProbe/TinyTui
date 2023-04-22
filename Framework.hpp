#ifndef FRAMEWORK_HPP_TINY_
#define FRAMEWORK_HPP_TINY_

#define COLOR_MAX 8
#define CLRIX(F, B) (COLOR_MAX * (F) + (B))
#define CLRPR(F, B) COLOR_PAIR(CLRIX(F, B))

#include <stddef.h>		// for size_t

class Framework {
protected:
	Framework();
	virtual ~Framework();

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

extern int __current_key;

#endif
