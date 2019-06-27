#ifndef LIGHTVOLUMETRIC_H
#define LIGHTVOLUMETRIC_H

#include "vector"
#include "Light.h"
#include "LightPuntual.h"

class LightVolumetric: public Light
{
public:
    LightVolumetric(vec3 point);
    LightVolumetric(vec3 point, vec3 am, vec3 d, vec3 s);
    LightVolumetric(vec3 point, vec3 am, vec3 d, vec3 s, float a, float b, float c);
    ~LightVolumetric();

    vec3 center;
    float distance = 1.0;

    // Vector de llums que composen la llum volumetrica
    std::vector<Light*> composition;

};

#endif // LIGHTVOLUMETRIC_H
