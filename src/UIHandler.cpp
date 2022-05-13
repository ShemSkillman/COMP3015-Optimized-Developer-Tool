#include "UIHandler.h"

UIHandler::UIHandler(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 400");
	ImGui::StyleColorsDark();

	waveColor = glm::vec3(0.2f, 0.5f, 0.9f);
}

void UIHandler::Poll()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Console");

	ImGui::SliderFloat("Wave Frequency", &freq, 0.1, 5, "%.2f", 1);

	ImGui::SliderFloat("Wave move speed", &velocity, 0.1, 20, "%.2f", 1);

	ImGui::SliderFloat("Wave Height", &amp, 0.1, 5, "%.2f", 1);

	const char* label = "test";
	float col[3] = { waveColor.x, waveColor.y, waveColor.z };
	if (ImGui::ColorPicker3(label, col))
	{
		waveColor = glm::vec3(col[0], col[1], col[2]);
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

float UIHandler::GetAmplitude()
{
	return amp;
}

float UIHandler::GetFrequency()
{
	return freq;
}

float UIHandler::GetVelocity()
{
	return velocity;
}

glm::vec3 UIHandler::GetWaveColor()
{
	return waveColor;
}