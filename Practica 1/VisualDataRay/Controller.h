#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "RenderFactory.h"
#include "SceneFactory.h"
#include "SceneFactoryStatic.h"
#include "SceneFactoryTemporal.h"

class Controller
{
    Render *render;
    Scene *scene;
    ColorMap *colorMap;

public:
    Controller(RenderFactory::RENDER_TYPES  rt,
               SceneFactory::SCENE_FACTORIES s,
               ObjectFactory::OBJECT_TYPES);
    void start(int argc, char **argv);

private:
    static SceneFactory *createFactory( SceneFactory::SCENE_FACTORIES factory);

};

#endif // CONTROLLER_H
