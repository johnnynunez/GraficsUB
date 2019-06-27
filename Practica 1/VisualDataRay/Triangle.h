#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"
#include "Animation.h"
#include "Translate.h"
#include "Scale.h"

class Triangle : public Plane
{
public:
    Triangle(vec3 A,vec3 B, vec3 C, float data);
    Triangle(vec3 cord,float r, float d);
    virtual ~Triangle() {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual void aplicaTG(TG *t);
private:
    //EPSILON
    float const EPSILON = 0.001;
    // normal del pla del triangle
    vec3 normal;
    //vector de vertexs del triangle
    std::vector<vec3> vertexs;
    vec3 A,B,C;
};
#endif // TRIANGLE_H
