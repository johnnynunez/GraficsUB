#include "LightPuntual.h"

LightPuntual::LightPuntual(vec3 point): Light(point){
    this->position = point;
    this->diffuse = vec3(0.7,0.7,0.7);
    this->specular = vec3(1.0,1.0,1.0);
    this->ambient = vec3(0.3,0.3,0.3);
    this->a = 0.01;
    this->b = 0;
    this->c = 0.5;
}
LightPuntual::LightPuntual(vec3 point, vec3 am, vec3 d, vec3 s): Light(point){
    this->position = point;
    this->diffuse = d;
    this->specular = s;
    this->ambient = am;
    this->a = 0.01;
    this->b = 0;
    this->c = 0.5;
}
LightPuntual::LightPuntual(vec3 point, vec3 am, vec3 d, vec3 s, float a, float b, float c): Light(point){
    this->position = point;
    this->diffuse = d;
    this->specular = s;
    this->ambient = am;
    this->a = a;
    this->b = b;
    this->c = c;
}
