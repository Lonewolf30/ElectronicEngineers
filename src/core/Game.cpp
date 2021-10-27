#include "Game.h"

void Game::AddGameObject(const GameObject& object) {
	gameObjects.push_back(object);
}

vector<GameObject> Game::GetGameObjects() {
	return gameObjects;
}

void Game::CleanUp() {
	for(GameObject object : gameObjects){
		object.CleanUp();
	}
}
