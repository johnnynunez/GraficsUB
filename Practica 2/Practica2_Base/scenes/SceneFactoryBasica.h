#ifndef SCENEFACTORYBASICA_H
#define SCENEFACTORYBASICA_H

#include "SceneFactory.h"

class SceneFactoryBasica : public SceneFactory
{
public:
    SceneFactoryBasica();

    virtual Scene    *getScene();
    virtual ColorMap *getColorMap();

};

#endif // SCENEFACTORYBASICA_H
