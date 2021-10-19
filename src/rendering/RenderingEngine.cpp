#include "RenderingEngine.h"

#include "../core/Time.h"
#include "../scene/MainMenu.h"
#include <thread>

RenderingEngine::RenderingEngine() {
	mainDisplay = Display();
	mouse = Mouse(&mainDisplay);
	keyboard = Keyboard(&mainDisplay);
	currentGame = &Game();

	userInterface = OpenGLShader("userinterface");

	isRunning = false;
	frameTime = 1.0 / 60.0;
}

void RenderingEngine::Start() {
	if (isRunning)
		return;

	Run();
}

void RenderingEngine::Stop() {
	if (!isRunning)
		return;

	isRunning = false;
}

void RenderingEngine::Run() {
	printf("Starting Engine \n");
	isRunning = true;

	Initialise();

	int frames = 0;


	double passedTime = 0;
	double unprocessedTime = 0;

	auto timePast = NanoTime();
	while (isRunning) {
		bool render = false;
		auto timeCurrent = NanoTime();
		auto pastTime = GetDuration<double>(timeCurrent, timePast);
		timePast = timeCurrent;

		passedTime += pastTime;
		unprocessedTime += pastTime;

		while (unprocessedTime > frameTime) {
			unprocessedTime -= frameTime;
			render = true;

			if (mainDisplay.IsCloseRequested())
				Stop();

			if (passedTime >= 1) {
				printf("Frames: %d \n", frames);
				frames = 0;
				passedTime = 0;
			}
		}

		if (render) {
			Render();
			frames++;
		} else {
			std::this_thread::sleep_for(1ms);
		}
	}

	CleanUp();
}

void RenderingEngine::Initialise() {
	configuration.LoadConfigurations();

	mainDisplay.CreateDisplay(&configuration);

	InitialiseMainMenu(currentGame);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	//TODO: OpenGL Rendering
	userInterface.Initialise();

	//TODO: Vulkan Init

	//TODO: OpenGLShader Init

	//TODO: SwapChainCreation
}

void RenderingEngine::Render() {
	currentGame->InputAll(mouse, keyboard);
	currentGame->UpdateAll2D(frameTime);

	mouse.Update();
	keyboard.Update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentGame->RenderAll2D(userInterface, mainDisplay.GetDisplaySize());

	mainDisplay.SwapBuffers();
	Display::PollEvents();
}

void RenderingEngine::CleanUp() {
	mainDisplay.CleanUp(&configuration);

	if(configuration.HasConfigurationChanged())
		configuration.SaveConfigurations();
}

void RenderingEngine::SetGame(Game* game) {
	this->currentGame = game;
}