#include "Object.h"

Object::Object(float d)
{
    data = d;
    material = nullptr;
}

Object::~Object()
{
    if (material!=nullptr){
        if (dynamic_cast<Lambertian *>(material))
            delete dynamic_cast<Lambertian *> (material);
        if (dynamic_cast<Ground *>(material))
            delete dynamic_cast<Ground *> (material);
        if (dynamic_cast<Metal *>(material))
            delete dynamic_cast<Metal *> (material);
        if (dynamic_cast<Transparent *>(material))
            delete dynamic_cast<Transparent *> (material);
    }
}

float Object::getData() {
    return data;
}

void Object::setMaterial(Material *m) {
    material = m;
}
