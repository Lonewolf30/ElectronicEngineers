#ifndef ELECTRONICENGINEERS_ISCALER_H
#define ELECTRONICENGINEERS_ISCALER_H

#include "../../../core/vec2/Vector2d.h"
#include "../../UiObject.h"

class IScaler {
public:
	virtual void GetWidth() = 0;

	virtual void GetHeight() = 0;

	virtual void CalculateScale(Vector2d windowSize) = 0;

	virtual void SetParent(UiObject parent) = 0;
};

#endif
