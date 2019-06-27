#include "Metal.h"
Metal::Metal(const vec3& color) : Material()
{
    Kspecular = color;
}

Metal::Metal(const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, int shininess){//components i shininess
    this->Kambient = Ka;
    this->Kdiffuse = Kd;
    this->Kspecular = Ks;
    Kt = vec3(1) - this->Kspecular;
    this->shininess = shininess;
}

Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 v = reflect(normalize(rec.p - r_in.initialPoint()), rec.normal);//vector reflexat
    vec3 p0 = rec.p + vec3(EPSILON)*v;//evitem acné
    r_out =  Ray(p0,v);//raig reflectit
    color += Kspecular;//només especular
    return true;
}
