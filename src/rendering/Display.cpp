#include "Display.h"
#include "../core/Time.h"

Display::Display() {
	window = {};
	displaySize = new Vector2<int>(0,0);
	scrollOffset = new Vector2<double>(0,0);
	frameBufferResized = false;
}

void Display::CreateDisplay(Configuration* configuration) {

	auto start_tp = NanoTime();

	glfwInit();

	int height = stoi(configuration->GetConfiguration("displayHeight", "600"));
	int width = stoi(configuration->GetConfiguration("displayWidth", "800"));

	displaySize = new Vector2<int>(width,height);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, "Electronic Engineers", nullptr, nullptr);

	int xpos, ypos, mon_width, mon_height;
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos, &mon_width, &mon_height);
	Vector2<int> window_pos = (Vector2<int>(xpos, ypos) + (Vector2<int>(mon_width, mon_height)/2)) - (*displaySize)/(2);
	glfwSetWindowPos(window, window_pos.GetX(), window_pos.GetY());

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* _window, int width, int height) {
		auto display = reinterpret_cast<Display*>(glfwGetWindowUserPointer(_window));
		display->displaySize = new Vector2<int>(width, height);
		display->frameBufferResized = true;
	});
	glfwSetScrollCallback(window, [] (GLFWwindow* _window, double xOffset, double yOffset) {
		auto display = reinterpret_cast<Display*>(glfwGetWindowUserPointer(_window));
		display->scrollOffset = new Vector2<double>(xOffset,yOffset);
	});

	auto end_tp = NanoTime();
	auto timeTaken = GetDuration<double>(end_tp, start_tp);
	cout << timeTaken << "s taken to create display" << endl;
}

bool Display::IsCloseRequested() {
	return glfwWindowShouldClose(window);
}

Vector2<int>* Display::GetDisplaySize() {
	return displaySize;
}

void Display::PollEvents() {
	glfwPollEvents();
}

void Display::CleanUp(Configuration* configuration) {
	configuration->SetConfiguration("displayHeight", to_string(displaySize->GetY()));
	configuration->SetConfiguration("displayWidth" , to_string(displaySize->GetX()));

	glfwTerminate();
}

bool Display::GetKeyboardKeyState(int keyCode) {
	return glfwGetKey(window, keyCode);
}

bool Display::GetMouseButtonState(int mouseCode) {
	return glfwGetMouseButton(window, mouseCode);
}

Vector2<double> Display::GetMousePosition() {
	double x,y;

	glfwGetCursorPos(window, &x, &y);

	y = (y - 1) * -1;

	return {x,y};
}

bool Display::HasFrameBufferResized() {
	return frameBufferResized;
}

void Display::SetFrameBufferResized(bool resized) {
	frameBufferResized = resized;
}

const char **Display::GetGLFWExtensions(uint32_t* extensionCount) {
	const char ** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(extensionCount);

	return glfwExtensions;
}

void Display::CreateSurface(VkInstance instance, VkSurfaceKHR *surface) {
	if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
		throw runtime_error("Unable to create window Surface");
	}
}
