#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "Scale.h"

class Cube : public Object
{
public:
    Cube(vec3 costatb, vec3 costath, float data);
    virtual ~Cube() {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual void aplicaTG(TG *t);

private:
    vec3 minBoundary;
    vec3 maxBoundary;
    float data;
    float EPSILON = 0.001;
    vec3 cubeCenter;
    //Funciones complementarias
    static void swap(float& a, float& b){
        float t = b;
        b = a;
        a = t;
    }
    static bool equals(float a, float b, float e){
        return fabs(a-b) < e;
    }

};

#endif // CUBE_H
