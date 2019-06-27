#include "SceneFactoryTemporal.h"

SceneFactoryTemporal::SceneFactoryTemporal()
{

}

Scene *SceneFactoryTemporal::getScene(string nomFitxer, ObjectFactory::OBJECT_TYPES t) {

    Scene *s = new Scene();

    // creacio de la camera
    //vec3 lookfrom(0, 20, 30);
    vec3 lookfrom(0, 2, -20);
    vec3 lookat(0.0, 0.0, 0.0);

    float dist_to_focus = glm::distance(lookat, lookfrom);
    float aperture = 0.1;

    int pixelsX = 800;
    int pixelsY = 600;

    s->cam = new Camera(lookfrom, lookat, vec3(0,1,0), 35, pixelsX, pixelsY, aperture, dist_to_focus);

    //Read DATA
    dataReader(nomFitxer, s, t);

    //Terra de l'escena
    s->ground = new FittedPlane(vec3(0,1,0), vec3(0,-1,0), vec2(s->DIM_SCENE[0][0],s->DIM_SCENE[2][0]), vec2(s->DIM_SCENE[0][1],s->DIM_SCENE[2][1]),0.0f);
    s->ground->setMaterial(new MaterialTextura());

    /*//Light *standard = new Light(vec3(2,8,10));
    //s->lights.push_back(standard);
    Light *l1 = new LightPuntual(vec3(2,8,10),vec3(0.1,0.1,0.1),vec3(0.7,0.7,0.7),vec3(0.7,0.7,0.7),0,0,1);
    s->lights.push_back(l1);
    Light *l2 = new LightPuntual(vec3(-5,20,10),vec3(0.1,0.1,0.1),vec3(0.7,0.7,0.7),vec3(0.7,0.7,0.7),0,0,1);
    s->lights.push_back(l2);
    Light *l3 = new LightPuntual(vec3(2,8,-50),vec3(0.1,0.1,0.1),vec3(0.7,0.7,0.7),vec3(0.7,0.7,0.7),0,0,1);
    s->lights.push_back(l3);
    */
    LightVolumetric *lV = new LightVolumetric(vec3(0.0,6.0,0.0));
    s->lights.push_back(lV);


    s->Iglobal = vec3(0.02,0.02,0.02);

    return s;
}

ColorMap *SceneFactoryTemporal::getColorMap() {
    ColorMap *cm = new ColorMapStatic();
    return cm;
}

