#include "GameObject.h"

GameObject::GameObject() = default;

void GameObject::AddComponent(GameComponent* component) {
	gameComponents.push_back(component);
}

void GameObject::CleanUp() {
	for(GameComponent* component : gameComponents){
		component->CleanUp();
	}
}

vector<GameComponent*> GameObject::GetComponents() {
	return gameComponents;
}
