#ifndef COLORMAPBASED_H
#define COLORMAPBASED_H

#include "Material.h"
#include "ColorMap.h"

class ColorMapBased : public Material
{

public:
    ColorMapBased(ColorMap cm, float value);

    virtual ~ColorMapBased();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
};

#endif // COLORMAPBASED_H
