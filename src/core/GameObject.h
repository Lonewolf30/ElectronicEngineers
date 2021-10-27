#include <vector>
#include <cstdint>
#include <type_traits>

#include <iostream>

#ifndef ELECTRONICENGINEERS_GAMEOBJECT_H
#define ELECTRONICENGINEERS_GAMEOBJECT_H

#include "../game_components/GameComponent.h"

using namespace std;

class GameObject {
private:
	vector<GameComponent *> gameComponents;

public:
	GameObject();

	void AddComponent(GameComponent *component);

	vector<GameComponent *> GetComponents();

	void CleanUp();


	template<class T>
	vector<GameComponent *> GetComponentsOfType() {
		vector<GameComponent *> result;

		for (GameComponent *component: gameComponents) {
			if (auto *comp = dynamic_cast<T*>(component)) {
				result.push_back(comp);
			}
		}

		return result;
	};
};


#endif
