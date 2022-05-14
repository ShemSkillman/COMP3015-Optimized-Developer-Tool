#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "scene.h"

#include <glad/glad.h>
#include "glslprogram.h"
#include <plane.h>
#include <UIHandler.h>

#include <objmesh.h>
class Scene_Main : public Scene
{
private:
    UIHandler& uiHandler;

    GLSLProgram waveProg, waveNoiseProg;

    float angle, tPrev, rotSpeed;
    float time;

    void setMatrices();
    void compile();

    std::unique_ptr<ObjMesh> planeObj;


public:
    Scene_Main(UIHandler& uiHandler);

    void initScene();
    void update(float t);
    void render();
    void resize(int, int);
};

#endif // SCENE_MAIN_H
