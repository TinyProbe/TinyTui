#ifndef BUTTON_HPP_TINY_
#define BUTTON_HPP_TINY_

#include "Object.hpp"		// for inheritance

class Button : public Object {
	friend class Layout;

public:
	struct Border {
		char lt;
		char rt;
		char lb;
		char rb;
		char hor;
		char ver;
	};

private:
	Button();
	Button(const Button& rhs) = delete;
	~Button();

	virtual const Border& getBorder() const;
	virtual void setBorder(const Border& border);
	virtual bool getRenderBorder() const;
	virtual void setRenderBorder(bool render_border);

	virtual void update() override;
	virtual void render() override;

private:
	Border border;
	bool render_border;
};

#endif
