#ifndef LIGHT_H
#define LIGHT_H

#include "Ray.h"

class Light
{
public:
    Light(vec3 point);
    virtual ~Light(){}

    vec3 position;
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float a;
    float b;
    float c;
    float atenuation;
private:
    double const EPSILON = 0.0000000000001;
};

#endif // LIGHT_H
