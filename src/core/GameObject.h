#include "Mouse.h"
#include "Keyboard.h"
#include <map>
#include <vector>

class GameObject;

#ifndef ELECTRONICENGINEERS_GAMEOBJECT_H
#define ELECTRONICENGINEERS_GAMEOBJECT_H

#include "../game_components/GameComponent.h"

using namespace std;

class GameObject {
public:
	void InputAll(Mouse mouse, Keyboard keyboard);
	void UpdateAll(float delta);

	void AddComponent(unsigned int id, GameComponent component);
	void RemoveComponent(unsigned int id);

	void SetParent(GameObject* parent);
	GameObject* GetParent();

private:
	void Input(Mouse mouse, Keyboard keyboard);
	void Update(float delta);

	map<unsigned int, GameObject> children;
	map<unsigned int, GameComponent> components;
	GameObject* parent;
};

#endif
