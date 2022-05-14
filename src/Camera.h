#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	void processInput(GLFWwindow* window);
	glm::mat4 getView();

public:
	static Camera& getCamera();	

private:
	glm::vec3 cameraPos = glm::vec3(10.0f);
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
};