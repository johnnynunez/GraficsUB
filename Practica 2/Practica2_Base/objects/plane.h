#ifndef PLANE_H
#define PLANE_H

#include "library/Common.h"
#include "cara.h"
#include <QObject>
#include <vector>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "./TG/TG.h"
#include "Material.h"
#include"Object.h"

class Plane: public Object
{
public:
    Plane(vec4 i1, vec4 i2, vec4 i3, vec4 i4);
    ~Plane();
    virtual void toGPU(QGLShaderProgram *p);
    virtual void toGPUTexture(QGLShaderProgram *pr);
    virtual void draw();
    virtual void drawTexture();
    virtual void setTexture(QOpenGLTexture *t);
    virtual void aplicaTG(TG *tg);

};

#endif // PLANE_H
