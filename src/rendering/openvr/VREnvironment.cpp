#include "VREnvironment.h"

bool VREnvironment::IsVRPossible() {
	bool isRuntimeInstalled = VR_IsRuntimeInstalled();
	bool isHmdPresent = VR_IsHmdPresent();

	// TODO: More Complex Checks

	return isRuntimeInstalled && isHmdPresent;
}

VREnvironment::VREnvironment() {
	vrsystem = nullptr;
	compositor = nullptr;
}

void VREnvironment::Initialise() {

	EVRInitError *peError = nullptr;
	vrsystem = VR_Init(peError, vr::VRApplication_Scene);
}

void VREnvironment::CleanUp() {
	VR_Shutdown();
}

void VREnvironment::CleanRender() {
	compositor->ClearLastSubmittedFrame();
}

bool VREnvironment::Update() {
	if(vrsystem->ShouldApplicationPause()){
		return false;
	}



	return true;
}

void VREnvironment::Render(Texture_t* left, Texture_t* right) {
	compositor->Submit(Eye_Left, left, nullptr);
	compositor->Submit(Eye_Right, right, nullptr);
}


