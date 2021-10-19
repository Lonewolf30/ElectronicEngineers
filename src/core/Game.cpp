#include "Game.h"

#include <iostream>

using namespace std;

static auto gameObjects = map<int, GameObject>();
static auto userInterface = map<int, UiObject>();

Game::Game() = default;

void Game::RemoveObject(int id) {

}

void Game::AddObject(int id, const GameObject &object) {
	gameObjects.insert(pair<int, GameObject>(id, object));
}

void Game::InputAll(Mouse mouse, Keyboard keyboard) {
	for (auto &item: gameObjects) {
		item.second.InputAll(mouse, keyboard);
	}
	for (auto &item: userInterface) {
		item.second.Input(mouse, keyboard);
	}
}

void Game::UpdateAll(float delta) {

}

void Game::RenderAll2D(const OpenGLShader &shader, Vector2d displaySize) {
	for (auto &item: userInterface) {
		item.second.Render(shader, displaySize);
	}
}

void Game::AddObject(int id, const UiObject &object) {
	userInterface.insert(pair<int, UiObject>(id, object));
}

void Game::UpdateAll2D(double delta) {
	for (auto &item: userInterface) {
		item.second.Update(delta);
	}
}