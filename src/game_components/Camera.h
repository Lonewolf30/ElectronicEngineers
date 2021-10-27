#ifndef ELECTRONICENGINEERS_CAMERA_H
#define ELECTRONICENGINEERS_CAMERA_H

#include "GameComponent.h"
#include "../core/Matrix4f.h"

class Camera : public GameComponent {
private:

public:
	void TransformCamera();
};


#endif
