#include "TG.h"

TG::TG()
{
 matTG = mat4();
}

TG::~TG()
{

}

mat4 TG::getTG() {
    return matTG;
}
