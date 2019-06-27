#include "ObjectFactory.h"

ObjectFactory *ObjectFactory::instance = nullptr;

ObjectFactory::ObjectFactory()
{

}
Object *ObjectFactory::getObject(float x, float y, float z, float v, OBJECT_TYPES t)
{
    Object *o;
    switch (t) {
    case SPHERE:
        o = new Sphere(vec3(x,y,z), 1, v);
        break;
    case TRIANGLE:
        o = new Triangle(vec3(x,y,z),v,v);
        break;
    case MALLA:        
        o = new BoundaryObject("../VisualDataRay/resources/cavall2K.obj",v);
        o->aplicaTG(new Translate(vec3(-x,-y,-z)));
        break;
    case CILINDRE:
        o = new Cilindre(vec3(x,y,z),v,v);
        break;
    case CERCLE:
        o = new Circle(vec3(x,y,z),vec3(x,y,z),v);
        break;
    default:
        break;
    }
    return o;
}
