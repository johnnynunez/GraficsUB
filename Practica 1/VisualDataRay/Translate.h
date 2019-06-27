#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "TG.h"

class Translate : public TG
{
public:
    glm::vec3 traslation;
    Translate(glm::vec3 trasl);
    ~Translate();
};

#endif // TRANSLATE_H
