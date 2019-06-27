#ifndef CILINDRE_H
#define CILINDRE_H

#include "math.h"
#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "Circle.h"
#include "Scale.h"

class Cilindre: public Object
{
public:
    Cilindre(vec3 center, float radi,float high);
    virtual ~Cilindre();
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    bool cilindreHit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual void aplicaTG(TG *t);

private:
    //EPSILON
    double const EPSILON = 0.0000000000001;
    //Centre del cilindre
    vec3 center;
    //Radi del cilindre
    float radi;
    //alçada del cilindre
    float high;
    float factor;
    vec3 centerfactor;
    //Tapa de d'alt
    Circle *top1;
    //Tapa de abaix
    Circle *top2;
    //Normal top1
    vec3 n1;
    //Normal top2
    vec3 n2;
};

#endif // CILINDRE_H
