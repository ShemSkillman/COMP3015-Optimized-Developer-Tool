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
}

void Scene_Main::initScene()
{
    compile();

	view = glm::lookAt(vec3(10.0f),
		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

	waveProg.use();

	waveProg.setUniform("EdgeWidth", 0.005f);
	waveProg.setUniform("PctExtend", 0.1f);
	waveProg.setUniform("LineColor", vec4(1.0f, 1.0f, 1.0f, 1.0f));

	waveProg.setUniform("Light.Position", vec4(10.0f, 10.0f, 10.0f, 1.0f));
	waveProg.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);

	waveNoiseProg.use();

	waveNoiseProg.setUniform("EdgeWidth", 0.005f);
	waveNoiseProg.setUniform("PctExtend", 0.1f);
	waveNoiseProg.setUniform("LineColor", vec4(1.0f, 1.0f, 1.0f, 1.0f));

	waveNoiseProg.setUniform("Light.Position", vec4(10.0f, 10.0f, 10.0f, 1.0f));
	waveNoiseProg.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);

	GLuint noiseTex = NoiseTex::generatePeriodic2DTex(uiHandler.GetFrequency(), 0.5f, 100, 100);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, noiseTex);

	waveNoiseProg.setUniform("NoiseTex", 0);
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

	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void Scene_Main::update(float t)
{
	view = Camera::getCamera().getView();

	static float freq;
	if (freq != uiHandler.GetFrequency() && uiHandler.GetUseNoise())
	{
		freq = uiHandler.GetFrequency();

		initScene();

		return;
	}

	time = t;

	waveProg.use();

	waveProg.setUniform("Freq", uiHandler.GetFrequency());
	waveProg.setUniform("Velocity", uiHandler.GetVelocity());
	waveProg.setUniform("Amp", uiHandler.GetAmplitude());

	vec3 color = uiHandler.GetWaveColor();
	waveProg.setUniform("Material.Kd", color * 0.6f);
	waveProg.setUniform("Material.Ka", color);

	waveProg.setUniform("Time", time);

	waveNoiseProg.use();

	waveNoiseProg.setUniform("Material.Kd", color * 0.6f);
	waveNoiseProg.setUniform("Material.Ka", color);

	waveNoiseProg.setUniform("Freq", uiHandler.GetFrequency());
	waveNoiseProg.setUniform("Velocity", uiHandler.GetVelocity());
	waveNoiseProg.setUniform("Amp", uiHandler.GetAmplitude());

	waveNoiseProg.setUniform("Time", time);

	model = mat4(1.0f);
	setMatrices();

	if (uiHandler.GetUseNoise())
	{
		waveNoiseProg.use();
	}
	else
	{
		waveProg.use();
	}
}

void Scene_Main::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	planeObj->render();

	glFinish();
}

void Scene_Main::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;

	projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);
}

void Scene_Main::setMatrices()
{
	mat4 mv = view * model;
	waveProg.use();
	waveProg.setUniform("ModelViewMatrix", mv);
	waveProg.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	waveProg.setUniform("MVP", projection * mv);

	waveNoiseProg.use();
	waveNoiseProg.setUniform("ModelViewMatrix", mv);
	waveNoiseProg.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	waveNoiseProg.setUniform("MVP", projection * mv);
}