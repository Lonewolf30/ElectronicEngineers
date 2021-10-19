#ifndef ELECTRONICENGINEERS_RENDERINGENGINE_H
#define ELECTRONICENGINEERS_RENDERINGENGINE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "Display.h"
#include "../core/vec2/Vector2d.h"
#include "../core/Mouse.h"
#include "../core/Keyboard.h"
#include "../core/Game.h"
#include "../core/Configuration.h"

#include "./opengl/OpenGLShader.h"
#include "./opengl/OpenGLTexture.h"

class RenderingEngine {
public:
	RenderingEngine();
	void SetGame( Game* game);

	void Start();
	void Stop();

private:
	Display mainDisplay;
	Mouse mouse;
	Keyboard keyboard;

	OpenGLShader userInterface;
	Configuration configuration{"display"};

	Game* currentGame;
	double frameTime;
	bool isRunning;

	void Run();
	void Initialise();
	void CleanUp();

	void Render();
};


#endif
