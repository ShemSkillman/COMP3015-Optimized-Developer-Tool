#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "scene.h"

#include <glad/glad.h>
#include "glslprogram.h"
#include <plane.h>
#include <UIHandler.h>

class Scene_Main : public Scene
{
private:
    GLSLProgram prog;

    Plane plane;

    float angle;
    float time;

    void setMatrices();
    void compile();

public:
    Scene_Main();

    void initScene();
    void update( float t , UIHandler& uiHandler);
    void render();
    void resize(int, int);
};

#endif // SCENE_MAIN_H
