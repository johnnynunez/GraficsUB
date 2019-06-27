#ifndef ANIMPPM_H
#define ANIMPPM_H

#include "RayTracingPPM.h"

class AnimPPM : public RayTracingPPM
{

public:
    AnimPPM(Scene *s);
    virtual ~AnimPPM();
    virtual void renderingScene();


};

#endif // ANIMPPM_H
