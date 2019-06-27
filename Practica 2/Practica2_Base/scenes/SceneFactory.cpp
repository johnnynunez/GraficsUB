#include "SceneFactory.h"

SceneFactory::SceneFactory()
{

}

SceneFactory::~SceneFactory()
{
}


// TO DO: A modificar per a adaptar el codi de la pràctica 1 a aquest nou dataReader on només
// es tenen en compte objectes
// de tipus BoundaryObjects. Suposo que el Boundary Objecte que està codificat en el fitxer
// està centrat en el 0 i amb escala unitaria.


void SceneFactory::dataReader (QString filename, QString obj, float dimVirtual[3][2], Scene *s) {

    // TO DO: Fase 1: Cal posar els valors de dimVirtual a les dimensions de l'escena

    QFile file(filename); // fitxer de dades
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {

            int numData;
            int numSeries;
            float dim[3][2];

            // Lectura de les dimensions de les dades originals
            for (int i = 0; i<3; i++) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));

                dim[i][0] = lineParts.at(0).toFloat();
                dim[i][1] = lineParts.at(1).toFloat();
            }


            // TO DO: Fase 1: Cal crear la textura a l'escena
            QString nomTextura = file.readLine().trimmed();
            //crear pla?

            // Lectura del numero de series temporals
            QString lineSerie = file.readLine().trimmed();
            numSeries = lineSerie.toInt();

            // Lectura del numero de dades en cada serie temporal
            QString lineDades = file.readLine().trimmed();
            numData = lineDades.toInt();


            for (int k=0; k<numSeries; k++) {
                for (int i=0; i<numData; i++) {
                    QString line = file.readLine().trimmed();
                    QStringList lineParts = line.split(QRegularExpression("\\s+"));

                    //assert (lineParts.count() == 3);

                    double x = lineParts.at(0).toFloat();
                    double z = lineParts.at(1).toFloat();
                    double v = lineParts.at(2).toFloat();
                    //reescalado de las variables
                    x = (((x - dim[0][0])*(dimVirtual[0][1] - dimVirtual[0][0]))/(dim[0][1] - dim[0][0])) + dimVirtual[0][0];
                    z = (((z - dim[1][0])*(dimVirtual[2][1] - dimVirtual[2][0]))/(dim[1][1] - dim[1][0])) + dimVirtual[2][0];
                    if(v > dimVirtual[2][1] || v < dimVirtual[2][0]){
                        v = (((v - dim[1][0])*(dimVirtual[2][1] - dimVirtual[2][0]))/(dim[2][1] - dim[1][0])) + dimVirtual[2][0];
                    }
    


                    // Por cada linea del fichero que no son header, cal fer un objecte
                    Object *o;
                    o = new Object(1000000, obj);
                    Capsa3D capsa = o->calculCapsa3D();
                    vec3 centre = capsa.pmin + vec3(capsa.a/2,capsa.h/2,capsa.p/2);
                    o->aplicaTG(new Sca(vec3(1/capsa.a,1/capsa.h,1/capsa.p)));
                    o->aplicaTG(new Trans(-centre));
                    o->aplicaTG(new Sca(vec3(v,v,v)));
                    o->aplicaTG(new Trans(vec3(x,1,z)));
                    /*Animation *right = new Animation();
                    right->frameIni = 0;
                    right->frameFinal = 5;
                    right->transf = new Trans(vec3(3,0,0));
                    o->addAnimation(right);*/
                    s->elements.push_back(o);

                    //traslacio de l'objecte al centre
                    //escala l'objecte a una unitat

                }
            }
            Plane *p = new Plane(vec4(dimVirtual[0][0],0,dimVirtual[2][0],1),vec4(dimVirtual[0][1],0,dimVirtual[2][0],1),vec4(dimVirtual[0][0],0,dimVirtual[2][1],1),vec4(dimVirtual[0][1],0,dimVirtual[2][1],1));
            s->elements.push_back(p);
            file.close();
        }
    }
}

