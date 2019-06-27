#ifndef TG_H
#define TG_H

/*#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"*/

#include "./library/mat.h"

using namespace Common;

class TG
{
public:
    mat4 matTG;
    TG();
    ~TG();
    virtual mat4 getTG();
};

#endif // TG_H
