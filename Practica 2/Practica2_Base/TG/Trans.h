#ifndef TRANS_H
#define TRANS_H

#include "TG.h"
using namespace Common;
class Trans : public TG
{
public:
    vec3 traslation;
    Trans(vec3 trasl);
    ~Trans();
};

#endif // TRANS_H
