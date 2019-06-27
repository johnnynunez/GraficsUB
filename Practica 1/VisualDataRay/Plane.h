#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"


class Plane: public Object{
public:
    Plane(vec3 normal, vec3 pass_point, float d);
    virtual ~Plane(){}
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const;
    virtual void aplicaTG(TG *t);

private:
    vec3 normal;
    vec3 point;
};

#endif // PLANE_H
