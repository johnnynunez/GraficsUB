#include "LightVolumetric.h"

LightVolumetric::LightVolumetric(vec3 point): Light(point){
    this->center = point;
    vec3 am = vec3(0.01,0.01,0.01);
    vec3 d = vec3(0.1,0.1,0.1);
    vec3 s = vec3(0.05,0.05,0.05);

    Light *l1 = new LightPuntual(point, am, d, s);
    Light *l2 = new LightPuntual(vec3(point.x+distance,point.y,point.z), am, d, s);
    Light *l3 = new LightPuntual(vec3(point.x-distance,point.y,point.z), am, d, s);
    Light *l4 = new LightPuntual(vec3(point.x,point.y,point.z+distance), am, d, s);
    Light *l5 = new LightPuntual(vec3(point.x,point.y,point.z-distance), am, d, s);
    Light *l6 = new LightPuntual(vec3(point.x,point.y+distance,point.z), am, d, s);
    Light *l7 = new LightPuntual(vec3(point.x,point.y-distance,point.z), am, d, s);

    this->composition.push_back(l1);
    this->composition.push_back(l2);
    this->composition.push_back(l3);
    this->composition.push_back(l4);
    this->composition.push_back(l5);
    this->composition.push_back(l6);
    this->composition.push_back(l7);
}

LightVolumetric::LightVolumetric(vec3 point, vec3 am, vec3 d, vec3 s): Light(point){
    this->center = point;
    am = vec3(am.x/7.0,am.y/7.0,am.z/7.0);
    d = vec3(d.x/7.0,d.y/7.0,d.z/7.0);
    s = vec3(s.x/7.0,s.y/7.0,s.z/7.0);

    Light *l1 = new LightPuntual(point, am, d, s);
    Light *l2 = new LightPuntual(vec3(point.x+distance,point.y,point.z), am, d, s);
    Light *l3 = new LightPuntual(vec3(point.x-distance,point.y,point.z), am, d, s);
    Light *l4 = new LightPuntual(vec3(point.x,point.y,point.z+distance), am, d, s);
    Light *l5 = new LightPuntual(vec3(point.x,point.y,point.z-distance), am, d, s);
    Light *l6 = new LightPuntual(vec3(point.x,point.y+distance,point.z), am, d, s);
    Light *l7 = new LightPuntual(vec3(point.x,point.y-distance,point.z), am, d, s);

    this->composition.push_back(l1);
    this->composition.push_back(l2);
    this->composition.push_back(l3);
    this->composition.push_back(l4);
    this->composition.push_back(l5);
    this->composition.push_back(l6);
    this->composition.push_back(l7);
}

LightVolumetric::LightVolumetric(vec3 point, vec3 am, vec3 d, vec3 s, float a, float b, float c): Light(point){
    this->center = point;
    am = vec3(am.x/7.0,am.y/7.0,am.z/7.0);
    d = vec3(d.x/7.0,d.y/7.0,d.z/7.0);
    s = vec3(s.x/7.0,s.y/7.0,s.z/7.0);

    Light *l1 = new LightPuntual(point, am, d, s, a, b, c);
    Light *l2 = new LightPuntual(vec3(point.x+distance,point.y,point.z), am, d, s, a, b, c);
    Light *l3 = new LightPuntual(vec3(point.x-distance,point.y,point.z), am, d, s, a, b, c);
    Light *l4 = new LightPuntual(vec3(point.x,point.y,point.z+distance), am, d, s, a, b, c);
    Light *l5 = new LightPuntual(vec3(point.x,point.y,point.z-distance), am, d, s, a, b, c);
    Light *l6 = new LightPuntual(vec3(point.x,point.y+distance,point.z), am, d, s, a, b, c);
    Light *l7 = new LightPuntual(vec3(point.x,point.y-distance,point.z), am, d, s, a, b, c);

    this->composition.push_back(l1);
    this->composition.push_back(l2);
    this->composition.push_back(l3);
    this->composition.push_back(l4);
    this->composition.push_back(l5);
    this->composition.push_back(l6);
    this->composition.push_back(l7);
}

LightVolumetric::~LightVolumetric(){
    for(unsigned int i = 0; i < composition.size(); ++i){
        if(composition[i]){
            if (dynamic_cast<LightPuntual*>(composition[i]))
                delete (LightPuntual *)(composition[i]);
        }
    }
}
