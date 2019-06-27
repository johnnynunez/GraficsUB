#include "SceneFactoryTemporal.h"

SceneFactoryTemporal::SceneFactoryTemporal(QString nomDades, QString nomObj, QString nomPaleta, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    nomFitxerDades = nomDades;
    nomFitxerObj = nomObj;
    nomFitxerColorMap = nomPaleta;
    dimVirtual[0][0] = xmin;
    dimVirtual[0][1] = xmax;
    dimVirtual[1][0] = ymin;
    dimVirtual[1][1] = ymax;
    dimVirtual[2][0] = zmin;
    dimVirtual[2][1] = zmax;
}

Scene *SceneFactoryTemporal::getScene() {
    // TO DO: Fase 3

    Scene *s = new Scene();
    return s;
}

ColorMap *SceneFactoryTemporal::getColorMap() {
    ColorMap *cm = new ColorMapStatic();
    return cm;
}

