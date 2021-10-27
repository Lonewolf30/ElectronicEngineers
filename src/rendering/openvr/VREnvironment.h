#include <openvr.h>

#ifndef ELECTRONICENGINEERS_VRENVIRONMENT_H
#define ELECTRONICENGINEERS_VRENVIRONMENT_H

using namespace vr;

class VREnvironment {
public:
	static bool IsVRPossible();
	VREnvironment();

	void Initialise();
	bool Update();
	void Render(Texture_t* left, Texture_t* right);
	void CleanUp();
	void CleanRender();
private:
	IVRSystem* vrsystem;
	IVRCompositor* compositor;

};


#endif
