#ifndef _CARA_H_
#define _CARA_H_

#include <vector>
#include "./library/Common.h"

using namespace std;

// Classe que representa una cara: cada cara pot tenir un color i
// i la llista d'indexs als vertexs que la formen. Llista ordenada en sentit antihorari

typedef vec4 Vertices;

class Cara
{
 public:
    Cara();

    Cara(int i1, int i2, int i3, int i4=-1);

    vec4 color;
    vector<int> idxVertices;
    vector<int> idxNormals;
    vector<int> idxTextures;

    vec3 normal;
    void calculaNormal(vector<Vertices> &);
};



#endif
