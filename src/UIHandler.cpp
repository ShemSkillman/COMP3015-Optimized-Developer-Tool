#include "UIHandler.h"

void UIHandler::Init(GLFWwindow* window)
{
	UIHandler::window = window;
}

void UIHandler::Poll()
{
	if (window == nullptr)
	{
		return;
	}
	else if (!initialized)
	{
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 400");
		ImGui::StyleColorsDark();

		initialized = true;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Console");

	ImGui::Text("Light Settings");
	
	AddSpacing(3);
	ImGui::SliderFloat("Light Intensity", &lightConfig.lightIntensity, 0.0f, 1.0f, "%.2f", 1);

	AddSpacing(3);
	ImGui::SliderInt("Cartoon Levels", &lightConfig.cartoonLevels, 1, 20, "%d", 1);

	AddSpacing(3);
	ImGui::SliderFloat("Light X Position", &lightConfig.lightPos.x, -50.0f, 50.0f, "%.2f", 1);

	AddSpacing(3);
	ImGui::SliderFloat("Light Y Position", &lightConfig.lightPos.y, 0.0f, 100.0f, "%.2f", 1);

	AddSpacing(3);
	ImGui::SliderFloat("Light Z Position", &lightConfig.lightPos.z, -50.0f, 50.0f, "%.2f", 1);

	AddSpacing(6);
	ImGui::Text("Wave Settings");

	AddSpacing(3);
	ImGui::SliderFloat("Wave Frequency", &waveConfig.frequency, 0.1, 5, "%.2f", 1);

	AddSpacing(3);
	ImGui::SliderFloat("Wave move speed", &waveConfig.velocity, 0.1, 20, "%.2f", 1);

	AddSpacing(3);
	ImGui::SliderFloat("Wave Height", &waveConfig.amplitude, 0.1, 20, "%.2f", 1);

	AddSpacing(3);
	ImGui::Checkbox("Use Noise", &waveConfig.useNoise);

	AddSpacing(3);
	float col[3] = { waveConfig.waveColor.x, waveConfig.waveColor.y, waveConfig.waveColor.z };
	if (ImGui::ColorPicker3("Wave Color", col))
	{
		waveConfig.waveColor = glm::vec3(col[0], col[1], col[2]);
	}

	AddSpacing(3);
	float waveLineCol[3] = { waveConfig.lineColor.x, waveConfig.lineColor.y, waveConfig.lineColor.z };
	if (ImGui::ColorPicker3("Wave Line Color", waveLineCol))
	{
		waveConfig.lineColor = glm::vec3(waveLineCol[0], waveLineCol[1], waveLineCol[2]);
	}

	AddSpacing(3);
	ImGui::SliderFloat("Wave Line Thickness", &waveConfig.lineThickness, 0.001f, 0.01f, "%.3f", 1);

	AddSpacing(6);
	ImGui::Text("Ship Settings");

	AddSpacing(3);
	ImGui::SliderFloat("Move Speed", &shipConfig.moveSpeed, 0.1f, 10.0f, "%.1f", 1);

	AddSpacing(3);
	ImGui::SliderAngle("Starting Y Rotation", &shipConfig.startingRotY, 0.0f, 360.0f);

	AddSpacing(3);
	ImGui::SliderAngle("Max X Rotation", &shipConfig.rotX, -90.0f, 90.0f);

	AddSpacing(3);
	ImGui::Checkbox("Invert X Rotation", &shipConfig.invertRotX);

	AddSpacing(3);
	ImGui::SliderAngle("Max Y Rotation", &shipConfig.rotY, -90.0f, 90.0f);

	AddSpacing(3);
	ImGui::Checkbox("Invert Y Rotation", &shipConfig.invertRotY);

	AddSpacing(3);
	ImGui::SliderAngle("Max Z Rotation", &shipConfig.rotZ, -90.0f, 90.0f);

	AddSpacing(3);
	ImGui::Checkbox("Invert Z Rotation", &shipConfig.invertRotZ);

	AddSpacing(3);
	ImGui::SliderFloat("Ship Y Position", &shipConfig.shipPosY, -10.0f, 10.0f, "%.2f", 1);

	AddSpacing(3);
	ImGui::SliderFloat("Bob Height", &shipConfig.bobHeight, 0.0f, 10.0f, "%.2f", 1);

	AddSpacing(3);
	ImGui::Checkbox("Invert Bob", &shipConfig.invertBob);

	AddSpacing(3);
	float shipCol[3] = { shipConfig.shipColor.x, shipConfig.shipColor.y, shipConfig.shipColor.z };
	if (ImGui::ColorPicker3("Ship Color", shipCol))
	{
		shipConfig.shipColor = glm::vec3(shipCol[0], shipCol[1], shipCol[2]);
	}	

	AddSpacing(3);
	float shipLineCol[3] = { shipConfig.lineColor.x, shipConfig.lineColor.y, shipConfig.lineColor.z };
	if (ImGui::ColorPicker3("Ship Line Color", shipLineCol))
	{
		shipConfig.lineColor = glm::vec3(shipLineCol[0], shipLineCol[1], shipLineCol[2]);
	}

	AddSpacing(3);
	ImGui::SliderFloat("Ship Line Thickness", &shipConfig.lineThickness, 0.0005f, 0.01f, "%.4f", 1);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

WaveConfig UIHandler::GetWaveConfig()
{
	return waveConfig;
}

LightConfig UIHandler::GetLightConfig()
{
	return lightConfig;
}

ShipConfig UIHandler::getShipConfig()
{
	return shipConfig;
}

void UIHandler::AddSpacing(int count)
{
	while (count > 0)
	{
		count--;
		ImGui::Spacing();
	}
}