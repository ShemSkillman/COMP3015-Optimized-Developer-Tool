#include "helper/scene.h"
#include "helper/scenerunner.h"
#include "scene_main.h"

int main(int argc, char* argv[])
{
	SceneRunner runner("Shader_Basics");

	std::unique_ptr<Scene> scene;

	scene = std::unique_ptr<Scene>(new Scene_Main());

	return runner.run(*scene);
}