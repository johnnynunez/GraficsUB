#ifndef CIRCLE_H
#define CIRCLE_H

#include "math.h"
#include "Plane.h"
#include "Animation.h"
#include "Translate.h"
#include "Scale.h"


class Circle: public Plane
{
public:
    Circle(vec3 normal, vec3 pass_point, float radius);
    virtual ~Circle(){}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual void aplicaTG(TG *t);
    float getCenterY();
    void setCenterY(float centery);

private:
    vec3 normal;
    vec3 center;
    float radius;
    double const EPSILON = 0.0000000000001;
};

#endif // CIRCLE_H

