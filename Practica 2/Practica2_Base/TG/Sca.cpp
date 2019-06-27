#include "Sca.h"

Sca::Sca(vec3 scal):scalation(scal){
    matTG[0][0] = scal.x;
    matTG[1][1] = scal.y;
    matTG[2][2] = scal.z;
}

Sca::~Sca(){

}
