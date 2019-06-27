#include "MaterialTextura.h"

MaterialTextura::MaterialTextura() :Material(){
    this->Kdiffuse = vec3(0.5,0.5,0.5);
    this->Kspecular = vec3(0.0,0.0,0.0);
    this->Kambient = vec3(0.1,0.1,0.1);
    this->opac = 1.0;
    this->shininess = 1.0;
}

MaterialTextura::~MaterialTextura()
{}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const {
    return false;
}
//Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta){
MaterialTextura::MaterialTextura(vec3 a, vec3 d, vec3 s, float o, int sh) :Material(a,d,s,o,sh){
    this->Kdiffuse = d;
    this->Kspecular = s;
    this->Kambient = a;
    if(o > 1.0+EPSILON){o = 1.0;}
    this->opac = o;
    if(sh > 500+EPSILON){sh = 500;}
    this->shininess = sh;
}

vec3 MaterialTextura::getDiffuse(vec2 point) const{
    return this->image->getColorPixel(point);
}

