#include "Ground.h"

Ground::Ground(const vec3& color): Material()
{
    this->Kdiffuse = color;

}

Ground::~Ground()
{
}

bool Ground::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {//es comporta como un lambert
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out =  Ray(rec.p, target-rec.p);
    color = Kdiffuse;
    return true;
}
