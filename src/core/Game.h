#ifndef ELECTRONICENGINEERS_GAME_H
#define ELECTRONICENGINEERS_GAME_H

#include "Keyboard.h"
#include "Mouse.h"

#include <map>
#include <string>

#include "GameObject.h"
#include "../rendering/opengl/OpenGLShader.h"
#include "../user_interface/UiObject.h"

using namespace std;

class Game {
public:
	Game();

	void InputAll(Mouse mouse, Keyboard keyboard);
	void UpdateAll(float delta);

	void UpdateAll2D(double delta);
	void RenderAll2D(const OpenGLShader& shader, Vector2d displaySize);

	void AddObject(int id,const UiObject& object);
	void AddObject(int id,const GameObject& object);
	void RemoveObject(int id);

private:
};


#endif
