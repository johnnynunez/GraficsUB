#include "Builder.h"

Builder::Builder(GLWidget *glWid)

{

    glWidget = glWid;
    scene = glWidget->getScene();

}

void Builder::newObjFromFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
            Object * obj = new Object(100000, fileName);
            scene->addObject(obj);
            scene->camera->actualitzaCamera(scene->capsaMinima);
            emit newObj(obj);
    }


}
void Builder::newStaticScene() {
    // creació de la nova Scena
    SceneFactory *sf = new SceneFactoryBasica();

    scene = sf->getScene();
    emit newScene(scene);
}


void Builder::newData(QString data, QString obj, QString colormap,
                      float xmin, float xmax, float ymin, float ymax,
                      float zmin, float zmax)
{
    // TO DO Fase 1: Crear la nova escena a partir de les dades
    // del dialeg

    // Per accedir a les dades del dialeg nomes cal accedir als atributs
    // de la classe dialeg: nomFitxerDades, nomFitxerObj, nomColorMap,
    // xmin, xmax, ymin, ymax, zmin i zmax

    SceneFactory *sf = new SceneFactoryStatic(data, obj, colormap, xmin, xmax,
                                              ymin, ymax, zmin, zmax);
    scene = sf->getScene();
    // TODO: A la fase 1: Afegir la possibilitat de llegir el colorMap de fitxer
    ColorMap *colorMap = sf->getColorMap();
    // TODO: A afegir de la pràctica 1 per a donar materials a l'escena
    // scene->setColorMap(colorMap);

    emit newScene(scene);
}

