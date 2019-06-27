#ifndef CYLINDER_H
#define CYLINDER_H

#include "math.h"
#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "Circle.h"

class Cylinder: public Object
{
public:
    Cylinder(vec3 cen, float r, float h);
    virtual ~Cylinder() {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;

    virtual void aplicaTG(TG *t);

private:
    //Centre del cilindre
    vec3 center;
    //Radi del cilindre
    float radius;
    //Alçada del cilindre
    float high;
    //Tapa de d'alt
    Circle *top1;
    //Tapa de abaix
    Circle *top2;
};

#endif // CYLINDER_H
