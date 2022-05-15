#include "scene_main.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
using std::cerr;
using std::endl;

#include "glutils.h"
#include "noisetex.h"
#include <GLFW/glfw3.h>
#include <Camera.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;

Scene_Main::Scene_Main(UIHandler& uiHandler) : time(0), uiHandler(uiHandler) {
	planeObj = ObjMesh::loadWithAdjacency("media/plane.obj");
	ship = ObjMesh::loadWithAdjacency("media/SHIP.obj");
}

void Scene_Main::initScene()
{
    compile();

	view = glm::lookAt(vec3(10.0f),
		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

	waveProg.use();
	waveProg.setUniform("PctExtend", 0.1f);

	basicProg.use();
	basicProg.setUniform("PctExtend", 0.1f);

	waveNoiseProg.use();
	waveNoiseProg.setUniform("PctExtend", 0.1f);
}

void Scene_Main::compile()
{
	try {
		waveProg.compileShader("shader/wave_anim_shader.vert");
		waveProg.compileShader("shader/wave_anim_shader.frag");
		waveProg.compileShader("shader/wave_anim_shader.geom");
		waveProg.link();

		waveNoiseProg.compileShader("shader/wave_anim_noise_shader.vert");
		waveNoiseProg.compileShader("shader/wave_anim_shader.frag");
		waveNoiseProg.compileShader("shader/wave_anim_shader.geom");
		waveNoiseProg.link();

		basicProg.compileShader("shader/basic_shader.vert");
		basicProg.compileShader("shader/wave_anim_shader.frag");
		basicProg.compileShader("shader/wave_anim_shader.geom");
		basicProg.link();

	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void Scene_Main::update(float t)
{
	view = Camera::getCamera().getView();

	// Regenerate noise map if frequency changed
	if (currentFreq != uiHandler.GetWaveConfig().frequency && uiHandler.GetWaveConfig().useNoise)
	{
		currentFreq = uiHandler.GetWaveConfig().frequency;
		GLuint noiseTex = NoiseTex::generatePeriodic2DTex(uiHandler.GetWaveConfig().frequency, 0.5f, 100, 100);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, noiseTex);

		waveNoiseProg.setUniform("NoiseTex", 0);
	}

	time = t;

	WaveConfig waveConfig = uiHandler.GetWaveConfig();
	LightConfig lightConfig = uiHandler.GetLightConfig();
	ShipConfig shipConfig = uiHandler.getShipConfig();

	// UPDATE WAVE PROGRAM //

	waveProg.use();

	waveProg.setUniform("Freq", waveConfig.frequency);
	waveProg.setUniform("Velocity", waveConfig.velocity);
	waveProg.setUniform("Amp", waveConfig.amplitude);

	waveProg.setUniform("LineColor", vec4(waveConfig.lineColor, 1.0f));
	waveProg.setUniform("EdgeWidth", waveConfig.lineThickness);

	waveProg.setUniform("Material.Kd", waveConfig.waveColor * 0.6f);
	waveProg.setUniform("Material.Ka", waveConfig.waveColor);

	waveProg.setUniform("Time", time);

	waveProg.setUniform("Light.Position", vec4(lightConfig.lightPos, 1.0f));
	waveProg.setUniform("Light.Intensity", vec3(1.0f) * lightConfig.lightIntensity);

	waveProg.setUniform("Levels", lightConfig.cartoonLevels);

	// UPDATE SHIP PROGRAM //

	basicProg.use();

	basicProg.setUniform("Material.Kd", shipConfig.shipColor * 0.6f);
	basicProg.setUniform("Material.Ka", shipConfig.shipColor);

	basicProg.setUniform("LineColor", vec4(shipConfig.lineColor, 1.0f));
	basicProg.setUniform("EdgeWidth", shipConfig.lineThickness);

	basicProg.setUniform("Light.Position", vec4(lightConfig.lightPos, 1.0f));
	basicProg.setUniform("Light.Intensity", vec3(1.0f) * lightConfig.lightIntensity);

	basicProg.setUniform("Levels", lightConfig.cartoonLevels);

	// UPDATE WAVE NOISE PROGRAM //

	waveNoiseProg.use();

	waveNoiseProg.setUniform("Material.Kd", waveConfig.waveColor * 0.6f);
	waveNoiseProg.setUniform("Material.Ka", waveConfig.waveColor);

	waveNoiseProg.setUniform("LineColor", vec4(waveConfig.lineColor, 1.0f));
	waveNoiseProg.setUniform("EdgeWidth", waveConfig.lineThickness);

	waveNoiseProg.setUniform("Freq", waveConfig.frequency);
	waveNoiseProg.setUniform("Velocity", waveConfig.velocity);
	waveNoiseProg.setUniform("Amp", waveConfig.amplitude);

	waveNoiseProg.setUniform("Time", time);	

	waveNoiseProg.setUniform("Light.Position", vec4(lightConfig.lightPos, 1.0f));
	waveNoiseProg.setUniform("Light.Intensity", vec3(1.0f) * lightConfig.lightIntensity);

	waveNoiseProg.setUniform("Levels", lightConfig.cartoonLevels);
}

void Scene_Main::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// RENDER WAVES //

	model = mat4(1.0f);

	if (uiHandler.GetWaveConfig().useNoise)
	{
		model = glm::translate(model, vec3(0.0f, -1.0f * uiHandler.GetWaveConfig().amplitude, 0.0f));
		setMatrices(waveNoiseProg);
	}
	else
	{
		setMatrices(waveProg);
	}

	planeObj->render();

	// RENDER SHIP //

	ShipConfig shipConfig = uiHandler.getShipConfig();

	model = mat4(1.0f);

	float sinValue = sin(time * shipConfig.moveSpeed);
	float cosValue = cos(time * shipConfig.moveSpeed);

	float bob = (shipConfig.bobHeight * (shipConfig.invertBob ? sinValue : cosValue));
	model = glm::translate(model, vec3(0.0f, shipConfig.shipPosY + bob, 0.0f));

	model = glm::rotate(model, shipConfig.startingRotY + shipConfig.rotY * (shipConfig.invertRotY ? sinValue : cosValue), glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::rotate(model, shipConfig.rotX * (shipConfig.invertRotX ? sinValue : cosValue), glm::vec3(1.0f, 0.0f, 0.0f));

	model = glm::rotate(model, shipConfig.rotZ * (shipConfig.invertRotZ ? sinValue : cosValue), glm::vec3(0.0f, 0.0f, 1.0f));

	setMatrices(basicProg);

	ship->render();

	glFinish();
}

void Scene_Main::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;

	projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);
}

void Scene_Main::setMatrices(GLSLProgram& prog)
{
	mat4 mv = view * model;

	prog.use();
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);
}