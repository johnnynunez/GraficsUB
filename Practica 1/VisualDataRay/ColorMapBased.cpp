#include "ColorMapBased.h"

ColorMapBased::ColorMapBased(ColorMap cm, float value):
    Material(vec3(0), cm.getColor(value), vec3(0), vec3(0), 1)
{
}


ColorMapBased::~ColorMapBased()
{
}

bool ColorMapBased::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out.push_back( Ray(rec.p, target-rec.p));
    color = diffuse;
    return true;
}

