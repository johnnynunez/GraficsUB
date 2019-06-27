#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include <string.h>

#include "Scene.h"
#include "ColorMap.h"
#include "ReadFile.h"
#include "ObjectFactory.h"

class SceneFactory
{
public:

    typedef enum
    {
           STATIC,
           TEMPORAL
    } SCENE_FACTORIES;


    virtual Scene    *getScene(string nomFitxer, ObjectFactory::OBJECT_TYPES t) = 0;
    virtual ColorMap *getColorMap() = 0;

protected :
    void dataReader (string filename, Scene *s, ObjectFactory::OBJECT_TYPES t);
};

#endif // SCENEFACTORY_H
