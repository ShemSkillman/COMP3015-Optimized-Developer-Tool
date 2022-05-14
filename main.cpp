#include "helper/scene.h"
#include "helper/scenerunner.h"
#include "scene_main.h"

int main(int argc, char* argv[])
{
	UIHandler uiHandler;
	SceneRunner runner("Shader_Basics", uiHandler);

	std::unique_ptr<Scene> scene;

	scene = std::unique_ptr<Scene>(new Scene_Main(uiHandler));

	return runner.run(*scene);
}