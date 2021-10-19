#include "Keyboard.h"

Keyboard::Keyboard() {
	display = {};
}

Keyboard::Keyboard(Display *display) {
	this->display = display;
}

bool Keyboard::GetKey(int keyCode) {
	return display->GetKeyboardKeyState(keyCode);
}

bool Keyboard::GetKeyDown(int keyCode) {
	return GetKey(keyCode) && !downKeys[keyCode];
}

bool Keyboard::GetKeyUp(int keyCode) {
	return !GetKey(keyCode) && downKeys[keyCode];
}

void Keyboard::Update() {
	for (int i = 0; i < NUM_KEY_CODES; i++)
		downKeys[i] = display->GetKeyboardKeyState(i);
}
