#include "Mouse.h"

Mouse::Mouse() {
	display = {};
}

Mouse::Mouse(Display *display) {
	this->display = display;
}

bool Mouse::GetMouse(int mouseCode) {
	return display->GetMouseButtonState(mouseCode);
}

bool Mouse::GetMouseDown(int mouseCode) {
	return GetMouse(mouseCode) && !mouseDown[mouseCode];
}

bool Mouse::GetMouseUp(int mouseCode) {
	return !GetMouse(mouseCode) && mouseDown[mouseCode];
}

void Mouse::Update() {
	for (int i = 0; i < NUM_MOUSE_CODES; ++i)
		mouseDown[i] = display->GetMouseButtonState(i);
}

Vector2d Mouse::GetMousePosition() {
	return display->GetMousePosition();
}
