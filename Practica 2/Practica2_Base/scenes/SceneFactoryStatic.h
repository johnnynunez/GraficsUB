#ifndef SCENEFACTORYSTATIC_H
#define SCENEFACTORYSTATIC_H

#include "SceneFactory.h"
#include "./colormaps/ColorMapStatic.h"

class SceneFactoryStatic : public SceneFactory
{
public:
    SceneFactoryStatic(QString nomDades, QString nomObj, QString nomPaleta,
                       float xmin, float xmax,
                       float ymin, float ymax,
                       float zmin, float zmax);

    virtual Scene    *getScene();
    virtual ColorMap *getColorMap();

private:
    QString nomFitxerDades;
    QString nomFitxerObj;
    QString nomFitxerColorMap;
    float dimVirtual[3][2];
};

#endif // SCENEFACTORYSTATIC_H
