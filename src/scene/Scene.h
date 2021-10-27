#ifndef ELECTRONICENGINEERS_SCENE_H
#define ELECTRONICENGINEERS_SCENE_H

#include "../core/Game.h"

class Scene {
public:
	virtual void Initialise(Game* game) = 0;
};

#endif
