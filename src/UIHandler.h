#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iomanip>

class UIHandler
{
public:
	UIHandler(GLFWwindow* window);
	void Poll();

private:
};