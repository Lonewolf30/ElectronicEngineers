#include "vec2/Vector2d.h"
#include "../rendering/Display.h"

#ifndef ELECTRONICENGINEERS_MOUSE_H
#define ELECTRONICENGINEERS_MOUSE_H

#define MOUSE_LEFT 0;
#define MOUSE_RIGHT 1;
#define MOUSE_MIDDLE 2;
#define MOUSE_FORWARD 3;
#define MOUSE_BACK 4;

const unsigned int NUM_MOUSE_CODES = 5;

class Mouse {

public:
	Mouse();
	explicit Mouse(Display* display);

	bool GetMouse(int mouseCode);
	bool GetMouseDown(int mouseCode);
	bool GetMouseUp(int mouseCode);

	void Update();

	Vector2d GetMousePosition();
private:
	bool mouseDown[NUM_MOUSE_CODES]{};
	Display* display;
};

#endif
