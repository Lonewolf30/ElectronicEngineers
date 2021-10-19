#ifndef ELECTRONICENGINEERS_MAINMENU_H
#define ELECTRONICENGINEERS_MAINMENU_H

#include "../core/Game.h"

inline void InitialiseMainMenu(Game* game) {
	UiObject testObject = UiObject();
	testObject.Initialise("test");
	game->AddObject(0, testObject);
}

#endif
