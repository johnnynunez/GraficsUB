#include "Controller.h"

Controller::Controller(RenderFactory::RENDER_TYPES rt, SceneFactory::SCENE_FACTORIES s, ObjectFactory::OBJECT_TYPES t)
{

    SceneFactory *scFac = createFactory(s);

    scene = scFac->getScene("../VisualDataRay/resources/dadesEuropa1.txt", t);
    colorMap = scFac->getColorMap();
    scene->setColorMap(colorMap);

    render = RenderFactory::getInstance()->getRender(rt);
    render->setScene(scene);

}

void Controller::start(int argc, char **argv) {

    render->startRendering(argc, argv);
}

SceneFactory* Controller::createFactory(SceneFactory::SCENE_FACTORIES factory)
{
    if(factory == SceneFactory::SCENE_FACTORIES::STATIC)
    {
        return new SceneFactoryStatic();
    }
    else if(factory == SceneFactory::SCENE_FACTORIES::TEMPORAL)
    {
        return new SceneFactoryTemporal();
    }
}
