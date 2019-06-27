#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material()
{
    Kdiffuse = color;
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();//vector reflectit a la intersecció usant la normal i certa aletorietat
    r_out =  Ray(rec.p, target-rec.p);//raig reflectit
    color = Kdiffuse;//reflecteix la component difosa només
    return true;
}

