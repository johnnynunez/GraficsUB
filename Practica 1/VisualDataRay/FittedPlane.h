#ifndef FITTEDPLANE_H
#define FITTEDPLANE_H

#include "Plane.h"
#include "Animation.h"
#include "Translate.h"
#include "Scale.h"

class FittedPlane: public Plane
{
public:
    FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d);
    virtual ~FittedPlane(){}
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const;
    virtual void aplicaTG(TG *t);

private:
    vec3 normal;
    vec3 point;
    vec2 minpoint;
    vec2 maxpoint;

    double const EPSILON = 0.0000000000001;
};

#endif // FITTEDPLANE_H
