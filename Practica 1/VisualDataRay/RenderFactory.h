#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H

#include "RayTracingGLU.h"
#include "RayTracingPPM.h"
#include "RayTracingTemps.h"

class RenderFactory
{
    static RenderFactory *instance;
    RenderFactory();

public:
    typedef enum  {
        ONLINE, IMAGE, TEMPORAL
    }RENDER_TYPES;

    static RenderFactory *getInstance() {
          if (instance==nullptr)
              instance = new RenderFactory();
          return instance;
    }
    Render *getRender(RENDER_TYPES t);
    ~RenderFactory() {
        delete instance;
    }

};

#endif // RENDERFACTORY_H
