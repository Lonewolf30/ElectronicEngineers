#ifndef ELECTRONICENGINEERS_RENDERINGENGINE_H
#define ELECTRONICENGINEERS_RENDERINGENGINE_H

#include "Display.h"
#include "../core/Vector2.h"
#include "../core/Mouse.h"
#include "../core/Keyboard.h"
#include "../core/Configuration.h"
#include "../core/Game.h"
#include "../scene/MainMenu.h"
#include "vulkan/VulkanRenderer.h"

class RenderingEngine {
public:
	RenderingEngine();

	void Start();
	void Stop();

	void LoadScene(Scene* scene);

private:
	VulkanRenderer* vulkan;
	Display* mainDisplay;
	Mouse* mouse;
	Keyboard* keyboard;
	Configuration* configuration;
	Game* game;

	double frameTime;
	bool isRunning;

	void Run();
	void Initialise();
	void CleanUp();

	void Render();
};


#endif
