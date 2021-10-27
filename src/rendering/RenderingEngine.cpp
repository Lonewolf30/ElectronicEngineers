#include "RenderingEngine.h"

#include "../core/Time.h"
#include <thread>

RenderingEngine::RenderingEngine() {
	mainDisplay = new Display();
	mouse = new Mouse(mainDisplay);
	keyboard = new Keyboard(mainDisplay);
	configuration = new Configuration("display");
	vulkan = new VulkanRenderer(mainDisplay, configuration);

	game = nullptr;

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

			if (mainDisplay->IsCloseRequested())
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

#include "../game_components/ModelRender.h"

void RenderingEngine::Initialise() {
	configuration->LoadConfigurations();
	// TODO Game Configurations

	mainDisplay->CreateDisplay(configuration);

	vulkan->SetGame(game);
	vulkan->Initialise();
}

void RenderingEngine::Render() {
	mouse->Update();
	keyboard->Update();

	vulkan->Draw();

	Display::PollEvents();
}

void RenderingEngine::CleanUp() {
	game->CleanUp();
	vulkan->CleanUp();
	mainDisplay->CleanUp(configuration);

	if(configuration->HasConfigurationChanged())
		configuration->SaveConfigurations();
}

void RenderingEngine::LoadScene(Scene* scene) {
	game = new Game();
	scene->Initialise(game);
}
