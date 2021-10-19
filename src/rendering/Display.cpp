#include "Display.h"
#include "../core/Time.h"

Display::Display() {
	window = {};
	frameBufferResized = false;
}

void Display::CreateDisplay(Configuration* configuration) {

	auto start_tp = NanoTime();

	glfwInit();

	int height = stoi(configuration->GetConfiguration("displayHeight", "600"));
	int width = stoi(configuration->GetConfiguration("displayWidth", "800"));

	displaySize = Vector2d(width,height);

	window = glfwCreateWindow(width, height, "Electronic Engineers", nullptr, nullptr);

	int xpos, ypos, mon_width, mon_height;
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos, &mon_width, &mon_height);
	Vector2d window_pos = (Vector2d(xpos, ypos) + (Vector2d(mon_width, mon_height)/2)) - displaySize/2;
	glfwSetWindowPos(window, static_cast<int>(window_pos.GetX()), static_cast<int>(window_pos.GetY()));

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* _window, int width, int height) {
		auto display = reinterpret_cast<Display*>(glfwGetWindowUserPointer(_window));
		display->displaySize = Vector2d(width, height);
		display->frameBufferResized = true;
		glViewport(0,0, width, height);

		int xpos, ypos, mon_width, mon_height;
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos, &mon_width, &mon_height);
		Vector2d window_pos = (Vector2d(xpos, ypos) + (Vector2d(mon_width, mon_height)/2)) - display->displaySize/2;
		glfwSetWindowPos(_window, static_cast<int>(window_pos.GetX()), static_cast<int>(window_pos.GetY()));
	});
	glfwSetScrollCallback(window, [] (GLFWwindow* _window, double xOffset, double yOffset) {
		auto display = reinterpret_cast<Display*>(glfwGetWindowUserPointer(_window));
		display->scrollOffset = Vector2d(xOffset,yOffset);
	});

	auto end_tp = NanoTime();
	auto timeTaken = GetDuration<double>(end_tp, start_tp);
	cout << timeTaken << "s taken to create display" << endl;
}

bool Display::IsCloseRequested() {
	return glfwWindowShouldClose(window);
}

Vector2d Display::GetDisplaySize() {
	return displaySize;
}

void Display::PollEvents() {
	glfwPollEvents();
}

void Display::CleanUp(Configuration* configuration) {
	configuration->SetConfiguration("displayHeight", to_string(displaySize.GetY()));
	configuration->SetConfiguration("displayWidth" , to_string(displaySize.GetX()));

	glfwTerminate();
}

bool Display::GetKeyboardKeyState(int keyCode) {
	return glfwGetKey(window, keyCode);
}

bool Display::GetMouseButtonState(int mouseCode) {
	return glfwGetMouseButton(window, mouseCode);
}

Vector2d Display::GetMousePosition() {
	double x,y;

	glfwGetCursorPos(window, &x, &y);

	y = (y - 1) * -1;

	return {x,y};
}

void Display::SwapBuffers() {
	glfwSwapBuffers(window);
}

bool Display::HasFrameBufferResized() {
	return frameBufferResized;
}

void Display::SetFrameBufferResized(bool resized) {
	frameBufferResized = resized;
}
