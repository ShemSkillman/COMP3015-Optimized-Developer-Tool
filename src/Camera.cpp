#include <Camera.h>

void Camera::processInput(GLFWwindow* window)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

	float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos.y -= cameraSpeed * 10;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos.y += cameraSpeed * 10;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos.x -= cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos.x += cameraSpeed;
}

glm::mat4 Camera::getView()
{
    const float radius = 20.0f;
    float camX = sin(cameraPos.x) * radius;
    float camZ = cos(cameraPos.x) * radius;

    cameraPos.y = glm::clamp(cameraPos.y, -5.0f, 40.0f);

	return glm::lookAt(glm::vec3(camX, cameraPos.y, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

Camera& Camera::getCamera()
{
    static Camera* cameraPtr;

    if (cameraPtr == nullptr)
    {
        cameraPtr = new Camera();
    }

    return *cameraPtr;
}