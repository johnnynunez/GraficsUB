#ifndef LIGHTPUNTUAL_H
#define LIGHTPUNTUAL_H

#include "Ray.h"
#include "Light.h"


class LightPuntual: public Light
{
public:
    LightPuntual(vec3 point);
    LightPuntual(vec3 point, vec3 am, vec3 d, vec3 s);
    LightPuntual(vec3 point, vec3 am, vec3 d, vec3 s, float a, float b, float c);
    ~LightPuntual(){}

private:
    double const EPSILON = 0.0000000000001;
};

#endif // LIGHTPUNTUAL_H
