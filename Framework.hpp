#ifndef FRAMEWORK_HPP_TINY_
#define FRAMEWORK_HPP_TINY_

#define COLOR_MAX 8
#define CLRIX(F, B) (COLOR_MAX * (F) + (B))
#define CLRPR(F, B) COLOR_PAIR(CLRIX(F, B))

#include <stddef.h>		// for size_t

class Framework {
protected:
	Framework();
	Framework(const Framework& rhs) = delete;
	virtual ~Framework();

	virtual void update() = 0;
	virtual void render() = 0;
};

#endif
