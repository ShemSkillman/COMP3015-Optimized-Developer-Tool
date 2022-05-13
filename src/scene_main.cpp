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

Scene_Main::Scene_Main() : time(0) {
	planeObj = ObjMesh::loadWithAdjacency("media/plane.obj");
}

void Scene_Main::initScene()
{
    compile();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

	view = glm::lookAt(vec3(10.0f),
		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	prog.setUniform("EdgeWidth", 0.005f);
	prog.setUniform("PctExtend", 0.1f);
	prog.setUniform("LineColor", vec4(1.0f, 1.0f, 1.0f, 1.0f));

	vec3 color = vec3(0.2f, 0.5f, 0.9f);
	prog.setUniform("Material.Kd", color * 0.6f);
	prog.setUniform("Material.Ka", color);

	prog.setUniform("Material.Ks", 0.2f, 0.2f, 0.2f);
	prog.setUniform("Material.Shininess", 100.0f);

	prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
	prog.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);
}

void Scene_Main::compile()
{
	try {
		prog.compileShader("shader/wave_anim_shader.vert");
		prog.compileShader("shader/wave_anim_shader.frag");
		prog.compileShader("shader/wave_anim_shader.geom");
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	prog.setUniform("Time", time);
	
	model = mat4(1.0f);
	setMatrices();

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
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);
}