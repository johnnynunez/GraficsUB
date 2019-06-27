#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"


// Classe abstracte Material. Totes les seves filles hauran de definoverrideir el metode abstracte sccater
class Material
{
public:

    Material();
    Material(vec3 a, vec3 d, vec3 s, float o, int sh);
    ~Material();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const = 0;
    vec3 multVec(float f,vec3 vec)const;
    virtual vec3 getDiffuse(vec2 point)const;

    vec3 Kdiffuse;
    vec3 Kspecular;
    vec3 Kambient;
    vec3 Kt = vec3(0);
    float opac;
    int shininess;
    double const EPSILON = 0.001;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
