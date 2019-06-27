#include "SceneFactoryBasica.h"

SceneFactoryBasica::SceneFactoryBasica()
{

}

Scene *SceneFactoryBasica::getScene() {
    Scene *scene = new Scene();

    QString s0("://resources/models/sphere0.obj");

    Light *l = new Light();
    l->setTipusLight(PUNTUAL);
    l->setAngle(30.0);
    l->setLightPosition(vec4(0.0,10.0,0.0,1.0));
    l->setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    scene->addLight(l);

    Object * obj = new Object(100000, s0);
    scene->addObject(obj);

    QString s1("://resources/models/sphere1.obj");
    Object * obj1 = new Object(100000, s1);
    scene->addObject(obj1);

    return scene;
}


ColorMap *SceneFactoryBasica::getColorMap() {
    return nullptr;
}

