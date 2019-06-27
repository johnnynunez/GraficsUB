#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Ray.h"
using namespace glm;


// Classe que codifica les propietats físiques de la càmera
class Camera {

public:

    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, int viewX, int viewY, float aperture, float focus_dist);
        // vfov is top to bottom in degrees

    Ray getRay(float s, float t) ;

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;

    float lens_radius;

    // Viewport: mides del frame buffer
    int viewportX;
    int viewportY;


    static vec3 random_in_unit_disk() {
        vec3 p;
        do {
            p = 2.0f*vec3(drand48(),drand48(),0) - vec3(1,1,0);
        } while (dot(p,p) >= 1.0);
        return p;
    }

};


#endif // CAMERA_H

