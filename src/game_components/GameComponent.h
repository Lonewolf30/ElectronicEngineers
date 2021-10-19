#include "../core/Mouse.h"
#include "../core/Keyboard.h"
#include "../core/GameObject.h"

class GameComponent;

#ifndef ELECTRONICENGINEERS_GAMECOMPONENT_H
#define ELECTRONICENGINEERS_GAMECOMPONENT_H

class GameComponent {
public:
	void Input(Mouse mouse, Keyboard keyboard) {};
	void Update(float delta) {};

	void Render2D() {};
	void Render3D() {};

private:
	GameObject* parent;
};

#endif
