#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#ifndef ELECTRONICENGINEERS_DISPLAY_H
#define ELECTRONICENGINEERS_DISPLAY_H

#include "../core/Vector2.h"
#include "../core/Configuration.h"

class Display {
public:
	Display();
	void CreateDisplay(Configuration* configuration);

	const char** GetGLFWExtensions(uint32_t* extensionCount);

	Vector2<int>* GetDisplaySize();
	Vector2<double> GetMousePosition();

	bool IsCloseRequested();

	bool GetMouseButtonState(int mouseCode);
	bool GetKeyboardKeyState(int keyCode);

	static void PollEvents();
	void CleanUp(Configuration* configuration);

	bool HasFrameBufferResized();
	void SetFrameBufferResized(bool resized);

	void CreateSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
	GLFWwindow* window;
	Vector2<int>* displaySize;
	Vector2<double>* scrollOffset;
	bool frameBufferResized;
};


#endif
