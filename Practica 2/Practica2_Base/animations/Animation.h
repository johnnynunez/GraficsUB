#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "./TG/TG.h"
#include <vector>
#include <QDebug>
#include <QMetaObject>

#define MAXFRAMES 1

class Animation
{
public:
 int frameIni;
 int frameFinal;
 TG  *transf;

 Animation(): frameIni(0), frameFinal(10), transf(NULL) {}

 //  "operator =" per la classe  Animation
 Animation &operator =(const Animation &rhs) {
   frameIni = rhs.frameIni;
   frameFinal = rhs.frameFinal;
   transf = rhs.transf;
   return *this;
 }
};

class Animable {
public:
    Animable();
    ~Animable();

    void addAnimation(Animation *anim);

    std::vector<Animation *> animFrames;
    // update recorre la llista de frames per detectar quina animació aplicar.
    // crida a aplicaTG quan l'ha trobada
    void update(int nframe);
    // Obliga als objectes que tenen animacions implementar aquest mètode
    virtual void aplicaTG(TG *tg) = 0;
};

#endif // ANIMATOR_H
