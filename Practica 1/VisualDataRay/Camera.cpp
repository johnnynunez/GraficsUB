#include "Camera.h"


Camera::Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, int viewX, int viewY, float aperture, float focus_dist) { // vfov is top to bottom in degrees
    float aspect = float(viewX)/float(viewY);
    viewportX = viewX;
    viewportY = viewY;
    lens_radius = aperture / 2;
    float theta = vfov*M_PI/180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);
    lower_left_corner = origin  - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
    horizontal = 2*half_width*focus_dist*u;
    vertical = 2*half_height*focus_dist*v;
}

Ray Camera::getRay(float s, float t) {
     return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
}


