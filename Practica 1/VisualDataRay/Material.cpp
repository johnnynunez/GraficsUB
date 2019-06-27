#include "Material.h"



Material::Material(){
    this->Kdiffuse = vec3(0.5,0.5,0.5);
    this->Kspecular = vec3(1.0,1.0,1.0);
    this->Kambient = vec3(0.2,0.2,0.2);
    this->opac = 1.0;
    this->shininess = 50.0;
}

Material::~Material()
{}

//Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta){
Material::Material(vec3 a, vec3 d, vec3 s, float o, int sh){
    this->Kdiffuse = d;
    this->Kspecular = s;
    this->Kambient = a;
    if(o > 1.0+EPSILON){o = 1.0;}
    this->opac = o;
    if(sh > 500+EPSILON){sh = 500;}
    this->shininess = sh;
}


vec3 Material::multVec(float f, vec3 vec) const{
    return vec3(vec.x*f,vec.y*f,vec.z*f);
}

vec3 Material::getDiffuse(vec2 point) const{
    return this->Kdiffuse;
}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}

