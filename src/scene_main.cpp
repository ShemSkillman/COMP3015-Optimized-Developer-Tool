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

using glm::vec3;
using glm::vec4;
using glm::mat4;

Scene_Main::Scene_Main() : time(0), plane(13.0f, 10.0f, 200, 2) {}

void Scene_Main::initScene()
{
    compile();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    prog.setUniform("Light.Intensity", vec3(1.0f, 1.0f, 1.0f));
    prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
    angle = glm::half_pi<float>();
}

void Scene_Main::compile()
{
	try {
		prog.compileShader("shader/wave_anim_shader.vert");
		prog.compileShader("shader/wave_anim_shader.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void Scene_Main::update( float t, UIHandler& uiHandler)
{
    time = t;

	prog.setUniform("Freq", uiHandler.GetFrequency());
	prog.setUniform("Velocity", uiHandler.GetVelocity());
	prog.setUniform("Amp", uiHandler.GetAmplitude());
}

void Scene_Main::render()
{
	prog.setUniform("Time", time);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = glm::lookAt(vec3(10.0f * cos(angle), 4.0f, 10.0f * sin(angle)),
		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);

	prog.setUniform("Material.Kd", 0.2f, 0.5f, 0.9f);
	prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	prog.setUniform("Material.Ka", 0.2f, 0.5f, 0.9f);
	prog.setUniform("Material.Shininess", 100.0f);
	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(-10.0f), vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(50.0f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	plane.render();
}

void Scene_Main::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void Scene_Main::setMatrices()
{
	mat4 mv = view * model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);
}