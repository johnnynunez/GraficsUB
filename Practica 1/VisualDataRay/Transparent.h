#ifndef TRANSPARENT_H
#define TRANSPARENT_H

#include "Material.h"

class Transparent : public Material
{

public:
    Transparent(const vec3& color);
    Transparent(vec3 ambient,vec3 diffuse, vec3 specular, float refractionIndex, float shininess);
    virtual ~Transparent();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    // índex de refracció
    float refractionIndex;
};
#endif // TRANSPARENT_H
