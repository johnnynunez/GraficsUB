#ifndef RayTracerPPM_h
#define RayTracerPPM_h

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

#include "Render.h"

class RayTracingPPM: public Render {
protected:
    ofstream myfile;
public:
    RayTracingPPM();
    virtual ~RayTracingPPM();

    virtual void initRender(string nomFitxer);
    virtual void setPixelColor(vec3 col, int x, int y);
    virtual void exitRender();

};
#endif

