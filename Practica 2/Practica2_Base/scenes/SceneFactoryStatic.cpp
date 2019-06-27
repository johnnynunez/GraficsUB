#include "SceneFactoryStatic.h"

SceneFactoryStatic::SceneFactoryStatic(QString nomDades, QString nomObj, QString nomPaleta, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
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

Scene *SceneFactoryStatic::getScene() {
    Scene *s = new Scene();

    // creacio de la camera
    vec3 lookfrom(3,2,2);
    //vec3 lookfrom(13, 2, 3);
    vec3 lookat(0,0,0);

    int pixelsX = 600;
    int pixelsY = 400;

    s->camera = new Camera(lookfrom, lookat, vec3(0,1,0), 90, pixelsX, pixelsY);

  // TO DO: Fase 1: construccio de l'escena

    // Read data
    dataReader(nomFitxerDades, nomFitxerObj, dimVirtual, s);
    Light *l = new Light();
    l->setTipusLight(PUNTUAL);
    l->setAngle(30.0);
    l->setLightPosition(vec4(0.0,10.0,0.0,1.0));
    l->setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    s->addLight(l);


    return s;
}

ColorMap *SceneFactoryStatic::getColorMap() {
    ColorMap *cm = new ColorMapStatic();
    return cm;
}

