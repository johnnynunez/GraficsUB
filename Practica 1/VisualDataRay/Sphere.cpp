#include "Sphere.h"

Sphere::Sphere(vec3 cen, float r, float d) :Object(d) {
    center = cen;
    radius = r;
    factor = d;
}

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {
    vec3 oc = r.initialPoint() - center;
    float a = dot(r.dirVector(), r.dirVector());
    float b = dot(oc, r.dirVector());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }
    return false;
}

void Sphere::aplicaTG(TG *t) {
    vec4 c(center, 1.0);
    c = t->getTG() * c;
    if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
    if(dynamic_cast<Scale *>(t)){
        this->radius = radius*this->factor;
    }
}

