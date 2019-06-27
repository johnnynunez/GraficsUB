#ifndef SceneFactoryTemporal_H
#define SceneFactoryTemporal_H

#include "SceneFactory.h"
#include "./colormaps/ColorMapStatic.h"

class SceneFactoryTemporal: public SceneFactory
{
public:
    SceneFactoryTemporal(QString nomDades, QString nomObj, QString nomPaleta,
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

#endif // SceneFactoryTemporal_H
