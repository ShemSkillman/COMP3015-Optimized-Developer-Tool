#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	void processInput(GLFWwindow* window);
	glm::mat4 getView();
	void setMouseInput(float xpos, float ypos);

public:
	static Camera& getCamera();
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);	

private:
	glm::vec3 cameraPos = glm::vec3(10.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	float lastX = 400;
	float lastY = 300;
	float yaw;
	float pitch;
	bool firstMouse = true;
};