#ifndef RAYTRACINGTEMPS_H
#define RAYTRACINGTEMPS_H

#include "RayTracingPPM.h"

class RayTracingTemps : public RayTracingPPM
{

public:
    RayTracingTemps();
    virtual ~RayTracingTemps();

    virtual void renderingScene();


};

#endif // RayTracingTemps_H
