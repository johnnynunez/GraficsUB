#include "Animation.h"

Animable::Animable()
{

}
Animable::~Animable()
{

}

void Animable::addAnimation(Animation *anim) {
    animFrames.push_back(anim);
}

void Animable::update(int nframe) {

    if(animFrames.size()==0){
        qDebug()<<"Object: has no animations yet!";
        return;
    }

    bool trobat = false;
    int i;
    for (i = 0; i<animFrames[animFrames.size()-1]->frameFinal && !trobat; i++)
        trobat = animFrames[i]->frameFinal>=nframe;

    aplicaTG(animFrames[i-1]->transf);
}
