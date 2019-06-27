#ifndef SceneFactoryTemporal_H
#define SceneFactoryTemporal_H

#include "SceneFactory.h"
#include "ColorMapStatic.h"

class SceneFactoryTemporal: public SceneFactory
{
public:
    SceneFactoryTemporal();
    virtual Scene    *getScene(string nomFitxer, ObjectFactory::OBJECT_TYPES t);
    virtual ColorMap *getColorMap();

};

#endif // SceneFactoryTemporal_H
