#ifndef ELECTRONICENGINEERS_ILOCATION_H
#define ELECTRONICENGINEERS_ILOCATION_H

#include "../../../core/vec2/Vector2d.h"
#include "../../UiObject.h"

class ILocation {
public:
	virtual void GetX() = 0;

	virtual void GetY() = 0;

	virtual void CalculateLocation(Vector2d windowSize) = 0;

	virtual void SetParent(UiObject parent) = 0;
};

#endif