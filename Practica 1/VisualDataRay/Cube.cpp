#include "Cube.h"



Cube::Cube(vec3 bmin, vec3 bmax, float data) : Object(data){

    minBoundary = bmin;
    maxBoundary = bmax;
    cubeCenter = (bmin + bmax) / 2.f;

    data = data;
}

bool Cube::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    float tmin, tmax;
    tmin = (minBoundary.x - r.origin.x) / r.direction.x;
    tmax = (maxBoundary.x - r.origin.x) / r.direction.x;
    if(tmin > tmax) swap(tmin, tmax);
    float tymin = (minBoundary.y - r.origin.y) / r.direction.y;
    float tymax = (maxBoundary.y - r.origin.y) / r.direction.y;

    if(tymin > tymax) swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;
    float tzmin = (minBoundary.z - r.origin.z) / r.direction.z;
    float tzmax = (maxBoundary.z - r.origin.z) / r.direction.z;

    if (tzmin > tzmax) swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;
    if(tmin > t_min && tmax < t_max){
        info.t = tmin;
        info.p = r.origin + (r.direction * tmin);
        info.mat_ptr = material;

        if(equals(info.p.x, maxBoundary.x, EPSILON))
            info.normal = vec3(1,0,0);

        if(equals(info.p.y, maxBoundary.y, EPSILON))
            info.normal = vec3(0,1,0);

        if(equals(info.p.z, maxBoundary.z, EPSILON))
            info.normal = vec3(0,0,1);
        if(equals(info.p.x, minBoundary.x, EPSILON))
            info.normal = vec3(-1,0,0);

        if(equals(info.p.y, minBoundary.y, EPSILON))
            info.normal = vec3(0,-1,0);

        if(equals(info.p.z, minBoundary.z, EPSILON))
            info.normal = vec3(0,0,-1);


        return true;
    }

    return false;

}

void Cube::aplicaTG(TG *t) {
    vec4 c(cubeCenter, 1.0);
    c = t->getTG() * c;
    if (dynamic_cast<Translate *>(t)) {//movem el centre
        cubeCenter.x = c.x; cubeCenter.y = c.y; cubeCenter.z = c.z;
    }
}
