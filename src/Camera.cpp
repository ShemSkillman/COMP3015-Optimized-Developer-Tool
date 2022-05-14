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

	return glm::lookAt(glm::vec3(camX, cameraPos.y, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera::getCamera().setMouseInput(xpos, ypos);
}

void Camera::setMouseInput(float xpos, float ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
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