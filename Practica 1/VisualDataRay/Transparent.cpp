#include "Transparent.h"

Transparent::Transparent(const vec3& color): Material()
{
    this->Kdiffuse = color;
}

Transparent::Transparent(vec3 ambient,vec3 diffuse, vec3 specular, float refractionIndex, float shininess): Material(ambient, diffuse, specular, shininess, shininess)
{
    this->Kambient = ambient;
    this->Kdiffuse = diffuse;
    this->Kspecular = specular;
    this->Kt = vec3(1.f);
    this->shininess = shininess;
    this->refractionIndex = refractionIndex;
}


Transparent::~Transparent()
{
}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 N = normalize(rec.normal);//Normal a la intersecció
    vec3 V = normalize(r_in.dirVector());//Vector del raig incident
    float cos = dot(N,V);//Cos de la Normal i el raig incident
    float snell = 1.0003f/refractionIndex;// medi2 / medi1
    vec3 p0 = rec.p;//punt d'intersecció

    if(cos > EPSILON){//Contrari
        N = -N;
        snell = 1.f/snell;
    }
    vec3 v_refract = refract(V,N,snell);// vector refractat normalitzat
    r_out = Ray(p0,v_refract);//raig refractat
    color = Kt;

    if(dot(v_refract,v_refract) < EPSILON){//No hi ha refracció sinó reflexió
        vec3 v_reflect = reflect(V,N);//vector reflectit normalitzat
        r_out = Ray(p0,v_reflect);//raig reflectit
        color = Kspecular;
    }

    return true;
}

