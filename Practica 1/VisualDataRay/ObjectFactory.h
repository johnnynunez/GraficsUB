#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Object.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Cilindre.h"
#include "BoundaryObject.h"
#include "Animation.h"

class ObjectFactory
{
    static ObjectFactory *instance;
    ObjectFactory();

public:
    typedef enum {
        SPHERE, TRIANGLE,MALLA,CILINDRE,CERCLE
    } OBJECT_TYPES;

    static ObjectFactory *getInstance() {
          if (instance==nullptr)
              instance = new ObjectFactory();
          return instance;
    }
    Object *getObject(float x, float y, float z, float val, OBJECT_TYPES t);
    ~ObjectFactory() {
        delete instance;
    }

};

#endif // OBJECTFACTORY_H
