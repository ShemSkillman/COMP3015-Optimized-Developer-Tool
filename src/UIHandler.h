#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iomanip>
#include <glm/glm.hpp>

class UIHandler
{
public:
	UIHandler();
	void Poll();
	void Init(GLFWwindow* window);

	float GetFrequency();
	float GetVelocity();
	float GetAmplitude();
	glm::vec3 GetWaveColor();
	bool GetUseNoise();
	bool IsFocused();


private:
	bool initialized = false;
	GLFWwindow* window;

	float freq = 1;
	float velocity = 4;
	float amp = 2;
	bool useNoise = false;
	glm::vec3 waveColor;
};