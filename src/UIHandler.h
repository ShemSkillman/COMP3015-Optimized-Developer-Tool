#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iomanip>
#include <glm/glm.hpp>

struct ShipConfig
{
	float moveSpeed = 1.0f;
	float rotX = 0.1f, rotY = 0.05f, rotZ = 0.08f;
	bool invertRotX = false, invertRotY = true, invertRotZ = false;
	float bobHeight = 0.25f, shipPosY = -0.6f;
	bool invertBob;
	glm::vec3 shipColor = glm::vec3(0.0f, 0.8f, 0.05f);
	glm::vec3 lineColor = glm::vec3(0.2f, 0.7f, 0.3f);;
	float lineThickness = 0.002f;
};

struct WaveConfig
{
	float frequency = 1, velocity = 4, amplitude = 2;
	bool useNoise = false;
	glm::vec3 waveColor = glm::vec3(0.2f, 0.5f, 0.9f), lineColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float lineThickness = 0.005f;;
};

class UIHandler
{
public:
	UIHandler();
	void Poll();
	void Init(GLFWwindow* window);

	bool IsFocused();
	ShipConfig getShipConfig();
	WaveConfig GetWaveConfig();


private:
	bool initialized = false;
	GLFWwindow* window;

	ShipConfig shipConfig;
	WaveConfig waveConfig;

private:
	void AddSpacing(int count);
};