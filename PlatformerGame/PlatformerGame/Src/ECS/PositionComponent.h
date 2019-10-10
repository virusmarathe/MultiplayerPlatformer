#pragma once

class PositionComponent : public Component
{
public:

	PositionComponent() : xpos(0), ypos(0) {}
	PositionComponent(float x, float y) : xpos(x), ypos(y) {}

	void update(float dt) override
	{
		xpos += dt * 0.05f;
	}

	float x() { return xpos; }
	float y() { return ypos; }

	void x(float val) { xpos = val; }
	void y(float val) { ypos = val; }

	void setPos(float x, float y) { xpos = x; ypos = y; }

private:
	float xpos;
	float ypos;
};