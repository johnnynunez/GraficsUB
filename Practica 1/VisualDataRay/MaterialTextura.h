#ifndef MATERIALTEXTURA_H
#define MATERIALTEXTURA_H

#include "Texture.h"
#include "Material.h"

class MaterialTextura: public Material
{
public:
    MaterialTextura();
    MaterialTextura(vec3 a, vec3 d, vec3 s, float o, int sh);
    virtual ~MaterialTextura();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    vec3 getDiffuse(vec2 point)const override;

    Texture *image = new Texture("://resources/europa.png");
};

#endif // MATERIALTEXTURA_H
