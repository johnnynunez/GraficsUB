#ifndef SCENE_H
#define SCENE_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>

#include "./library/Common.h"
#include "./objects/Object.h"
#include <Light.h>
#include <Camera.h>
#include "TG/Trans.h"
#include "TG/Sca.h"
#include "objects/plane.h"

using namespace std;

// Scene: contains all objects, lights to visualize the scene
// the viewer is placed in the z+ axis

class Scene {

public:

    vector<Object*> elements;
    vector<Light*>  lights;
    int MAX = 7;

    vec3 lightAmbientGlobal;
    Camera *camera;
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    Scene();
    ~Scene();

    void   addObject(Object *obj);
    void   addLight(Light *l);
    Light *getLightActual();
    void   setLightActual(Light* l);

    void setCamera(Camera *c);

    void toGPU(QGLShaderProgram *p);
    void LightsToGPU (QGLShaderProgram *program);
    void draw();
    void drawTexture();

    void setAmbientToGPU(QGLShaderProgram *program);

    void calculCapsaMinCont3DEscena();
    void update(int nframe);

};

#endif // SCENE_H
