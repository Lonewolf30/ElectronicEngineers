#include "../rendering/Display.h"

#ifndef ELECTRONICENGINEERS_KEYBOARD_H
#define ELECTRONICENGINEERS_KEYBOARD_H

const unsigned int NUM_KEY_CODES = 256;

class Keyboard {
public:
	Keyboard();
	explicit Keyboard(Display* display);

	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	void Update();
private:
	Display* display;
	bool downKeys[NUM_KEY_CODES]{false};

};


#endif
