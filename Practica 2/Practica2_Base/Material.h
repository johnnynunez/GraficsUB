#ifndef MATERIAL_H
#define MATERIAL_H

#include "library/Common.h"
#include <QGLShaderProgram>
// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();
    Material(vec4 Kd,vec4 Ks,vec4 Ka,float shine);
    void toGPU(QGLShaderProgram *program);

    vec4 Kd,Ks,Ka;
    float shine;

};

#endif // MATERIAL_H
