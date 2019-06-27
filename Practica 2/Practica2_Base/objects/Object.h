#ifndef Object_H
#define Object_H

#include <QObject>
#include <vector>
#include "./library/Common.h"
#include "./cara.h"
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "./TG/TG.h"
#include "./TG/Sca.h"
#include "./TG/Trans.h"
#include "./animations/Animation.h"
#include "Material.h"

using namespace std;

typedef Common::vec4  point4;

// Classe que conte la representacio d'un Objecte: geometria, topologia, material i textures
class Object : public QObject, public Animable {

    Q_OBJECT
protected:
    QString nom;
    vector<Cara> cares;
    vector<point4> vertexs;
    vector<vec4> normalsVertexs;
    vector<vec2>   textVertexs;
    vector<vec2> calculateCoord(vector<vec4> n);

    // Estructures per passar a la GPU
    GLuint buffer;
    GLuint vao;

    int     numPoints;
    point4 *points;
    point4 *normals;
    point4 *colors; // Els colors s'usen en la primera execució però després son prescindibles
    vec2 *textCoord;

    Material *mat;

    int Index; // index de control del numero de vertexs a passar a la GPU

    QGLShaderProgram *program;

    QOpenGLTexture *texture;

public:
    Object(const int npoints, QObject *parent = 0);
    Object(const int npoints, QString n);
    ~Object();

    void parseObjFile(const QString &fileName);

    void setTexture(QOpenGLTexture *t);

    virtual void make();
    virtual void toGPU(QGLShaderProgram *p);
    virtual void toGPUTexture(QGLShaderProgram *pr);

    //virtual void update();

    virtual void draw();
    virtual void drawTexture();

    Capsa3D calculCapsa3D();

    virtual void aplicaTG(TG *tg);

    void initTexture();
};



#endif // Object_H
