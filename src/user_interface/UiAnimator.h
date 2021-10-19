#ifndef ELECTRONICENGINEERS_UIANIMATOR_H
#define ELECTRONICENGINEERS_UIANIMATOR_H

#include "ui_modifier/ui_location/ILocation.h"
#include "ui_modifier/ui_scale/IScaler.h"

class UiAnimator {
public:
	UiAnimator();

private:
	ILocation* firstPos;
	ILocation* lastPos;
	IScaler* minScale;
	IScaler* maxScale;
};


#endif
