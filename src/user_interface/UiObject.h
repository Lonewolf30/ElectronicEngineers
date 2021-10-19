#ifndef ELECTRONICENGINEERS_UIOBJECT_H
#define ELECTRONICENGINEERS_UIOBJECT_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "../rendering/opengl/OpenGLShader.h"
#include "../rendering/opengl/OpenGLTexture.h"

#include "../core/Mouse.h"
#include "../core/Keyboard.h"

#include <string>

using namespace std;

class UiObject {
public:
	UiObject();
	void Initialise(string _texture);
	void Update(double delta);
	void Render(OpenGLShader shader, Vector2d displaySize);
	void Input(Mouse mouse, Keyboard keyboard);

private:
	OpenGLTexture texture;

	Vector2d offset = {0,0};
	Vector2d scale = {1,1};
};

#endif