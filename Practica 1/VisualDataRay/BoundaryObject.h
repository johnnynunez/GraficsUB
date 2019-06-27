#ifndef BOUNDARYOBJECT_H
#define BOUNDARYOBJECT_H

#include <vector>
#include <string>

#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.h"
#include "Cara.h"
#include "ReadFile.h"
#include "Triangle.h"
#include "Scale.h"
#include "Cube.h"


using namespace std;

class BoundaryObject : public Object
{
public:
    BoundaryObject(string s, float data);
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual void aplicaTG(TG *t);
    virtual ~BoundaryObject();

private:


    string nom;
    glm::vec3 centre;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vector<Triangle*> triangles;
    void readObj(string filename);
    void construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt);
    Cube* bounds;

};

#endif // BOUNDARYOBJECT_H
