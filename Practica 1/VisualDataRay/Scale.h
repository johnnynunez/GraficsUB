#ifndef SCALE_H
#define SCALE_H
#include "TG.h"
class Scale : public TG
{
public:
    glm::vec3 scalation;
    float escala;
    Scale(glm::vec3 scale);
    Scale(float esc);
    ~Scale();

};
#endif // SCALE_H
