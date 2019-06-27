#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Animation.h"
#include "Object.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Cilindre.h"
#include "Plane.h"
#include "FittedPlane.h"
#include "Metal.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "Ground.h"
#include "MaterialTextura.h"
#include "Camera.h"
#include "ColorMap.h"
#include "Light.h"
#include "LightVolumetric.h"

class Scene: public Hitable
{
    ColorMap *colorMap;

public:

    Scene();
    virtual ~Scene();

    void setColorMap(ColorMap *cm);

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;

    vec3 BlinnPhong(vec3 point, vec3 normal, const Material* material);
    vec3 ComputeLight(vec3 point, vec3 normal, const Material* material, Light *li);
    vec2 getUVPoint(vec3 point);
    void update(int nframe);

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth );

    // Vector d'objectes continguts a l'escena
    std::vector<Object*> objects;

    // Vector de llums contingudes a l'escena
    std::vector<Light*> lights;

    // Camera: on está l'observador
    Camera *cam;

    // Llum global
    vec3 Iglobal;

    //Terra de l'escena
    FittedPlane *ground;

    //XYZmin,XYZmax de l'escena
    float const DIM_SCENE[3][2] = {-50,50,-50,50,-50,50};

private:
    double const EPSILON = 0.01;
    int const MAX_DEPTH = 10;

};

#endif // SCENE_H
