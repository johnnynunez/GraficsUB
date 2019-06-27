#include "SceneFactoryAnimation.h"

SceneFactoryAnimation::SceneFactoryAnimation(QString nomDades, QString nomObj, QString nomPaleta, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
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

Scene *SceneFactoryAnimation::getScene() {
    // TO DO: Fase 3

    Scene *s = new Scene();
    QString s1("://resources/models/sphere1.obj");
    Object *obj1 = new Object(100000,s1);
    // ... Troç de codi just per a afegir animació a l'objecte
    Animation *anim = new Animation();

    anim->transf = new Trans(vec3(0.2));
    obj1->addAnimation(anim);
    s->elements.push_back(obj1);

    return s;
}

ColorMap *SceneFactoryAnimation::getColorMap() {
    ColorMap *cm = new ColorMapStatic();
    return cm;
}
