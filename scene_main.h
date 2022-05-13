#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

class Scene_Main : public Scene
{
private:
    GLuint vaoHandle;
    GLSLProgram prog;
    float angle;

    void compile();

public:
    Scene_Main();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENE_MAIN_H
