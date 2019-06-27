#pragma once

#include "Ray.h"
#include "Hitable.h"
#include "Material.h"
#include "Lambertian.h"
#include "Ground.h"
#include "Metal.h"
#include "Animation.h"
#include "Transparent.h"

// Es la classe pare de tots els objectes que s'han de visualitzar. Es fa una classe Objectes que hereda de Hitable
// i ha d'implementar el metode hit
class Object: public Hitable, public Animable {
  public:
    Object(float d);
    virtual ~Object();

    // Metodes a implementar en les classes filles: son  metodes abstractes
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const = 0;
    virtual void aplicaTG(TG *tg) = 0;

   float getData();
   void setMaterial(Material *m);

  protected:
    Material *material;   // Material de l'objecte
    float data; // valor de les dades que representa aquest objecte
};

// TODO: Cal definir els diferents tipus d'objectes de l'escena com a fills d'Object.
// Cal definir-lis els atributs propis i implementar
// el metode hit()

