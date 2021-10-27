#include <vector>

#ifndef ELECTRONICENGINEERS_GAME_H
#define ELECTRONICENGINEERS_GAME_H

#include "GameObject.h"

using namespace std;

class Game {

public:
	void AddGameObject(const GameObject& object);
	vector<GameObject> GetGameObjects();

	void CleanUp();

private:
	vector<GameObject> gameObjects;
};


#endif
