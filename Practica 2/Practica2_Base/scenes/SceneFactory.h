#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include "Scene.h"
#include "./colormaps/ColorMap.h"


class SceneFactory
{
public:

    typedef enum
    {
        BASICA,
        STATIC,
        TEMPORAL
    } SCENE_FACTORIES;

    SceneFactory();
    virtual Scene *getScene() = 0;
    virtual ColorMap *getColorMap() = 0;
    //virtual void *setColorMap()

    virtual ~SceneFactory();

protected:

    void dataReader (QString filename, QString obj, float dimVirtual[3][2], Scene *s);

};

#endif // SCENEFACTORY_H
