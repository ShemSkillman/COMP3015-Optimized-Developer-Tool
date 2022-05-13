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

	float GetFrequency();
	float GetVelocity();
	float GetAmplitude();

private:
	float freq = 2.5;
	float velocity = 2.5;
	float amp = 0.6;

};