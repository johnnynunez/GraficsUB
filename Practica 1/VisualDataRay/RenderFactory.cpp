#include "RenderFactory.h"

RenderFactory *RenderFactory::instance = nullptr;

RenderFactory::RenderFactory() {

}
Render *RenderFactory::getRender(RENDER_TYPES t)
{
    Render *r;
    switch (t) {
    case ONLINE:
        r = new RayTracingGLU();
        break;
    case IMAGE:
        r = new RayTracingPPM();
        break;
    case TEMPORAL:
        r = new RayTracingTemps();
        break;
         }
    return r;
}

