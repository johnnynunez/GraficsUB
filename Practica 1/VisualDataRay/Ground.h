#ifndef GROUND_H
#define GROUND_H

#include "Material.h"

class Ground : public Material
{
public:
    Ground(const vec3& color);
    virtual ~Ground();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
};

#endif // GROUND_H
