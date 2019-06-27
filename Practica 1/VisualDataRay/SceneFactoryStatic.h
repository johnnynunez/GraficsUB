#ifndef SCENEFACTORYSTATIC_H
#define SCENEFACTORYSTATIC_H

#include "SceneFactory.h"
#include "ColorMapStatic.h"

class SceneFactoryStatic : public SceneFactory
{
public:
    SceneFactoryStatic();

    virtual Scene    *getScene(string nomFitxer, ObjectFactory::OBJECT_TYPES t);
    virtual ColorMap *getColorMap();

};

#endif // SCENEFACTORYSTATIC_H
