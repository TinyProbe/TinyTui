#ifndef FRAMEWORK_HPP_TINY_
#define FRAMEWORK_HPP_TINY_

#include <cstdlib>

class Framework {
protected:
	Framework();
	virtual ~Framework();

	virtual size_t getRow() const;
	virtual size_t getCol() const;
	virtual int getY() const;
	virtual int getX() const;

	virtual void setSize(size_t row, size_t col);
	virtual void setAxis(int y, int x);

	virtual void update() = 0;
	virtual void render() = 0;

private:
	size_t row;
	size_t col;
	int y;
	int x;

};

#endif
