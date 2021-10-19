#include "GameObject.h"


void GameObject::InputAll(Mouse mouse, Keyboard keyboard) {

}

void GameObject::UpdateAll(float delta) {

}

void GameObject::Input(Mouse mouse, Keyboard keyboard) {
	for (auto &item : components) {
		item.second.Input(mouse, keyboard);
	}

	for (auto &item : children) {
		item.second.InputAll(mouse, keyboard);
	}
}

void GameObject::Update(float delta) {
	for (auto &item : components) {
		item.second.Update(delta);
	}

	for (auto &item : children) {
		item.second.Update(delta);
	}
}

GameObject *GameObject::GetParent() {
	return parent;
}

void GameObject::SetParent(GameObject *_parent) {
	this->parent = _parent;
}

void GameObject::AddComponent(unsigned int id, GameComponent component) {
	this->components.insert(pair<unsigned int, GameComponent>(id, component));
}

void GameObject::RemoveComponent(unsigned int id) {
	this->components.erase(id);
}