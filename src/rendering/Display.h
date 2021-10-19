#include <vulkan/vulkan.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#ifndef ELECTRONICENGINEERS_DISPLAY_H
#define ELECTRONICENGINEERS_DISPLAY_H

#include "../core/vec2/Vector2d.h"
#include "../core/Configuration.h"

class Display {
public:
	Display();
	void CreateDisplay(Configuration* configuration);
	void SwapBuffers();

	Vector2d GetDisplaySize();
	Vector2d GetMousePosition();

	bool IsCloseRequested();

	bool GetMouseButtonState(int mouseCode);
	bool GetKeyboardKeyState(int keyCode);

	static void PollEvents();
	void CleanUp(Configuration* configuration);

	bool HasFrameBufferResized();
	void SetFrameBufferResized(bool resized);

private:
	GLFWwindow* window;
	Vector2d displaySize = {0,0};
	Vector2d scrollOffset = {0,0};
	bool frameBufferResized;
};


#endif
