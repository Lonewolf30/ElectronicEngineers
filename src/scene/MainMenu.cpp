#include "MainMenu.h"

#include "../game_components/Camera.h"
#include "../game_components/ModelRender.h"

void MainMenu::Initialise(Game* game) {
	GameObject object = GameObject();
	ModelRender* component = new ModelRender();
	Camera* camera = new Camera();

	object.AddComponent(component);
	object.AddComponent(camera);
	game->AddGameObject(object);
}
