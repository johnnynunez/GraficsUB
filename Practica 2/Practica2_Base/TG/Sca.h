#ifndef SCA_H
#define SCA_H

#include "TG.h"
using namespace Common;

class Sca : public TG
{
public:
    vec3 scalation;
    Sca(vec3 scal);
    ~Sca();
};

#endif // SCA_H
