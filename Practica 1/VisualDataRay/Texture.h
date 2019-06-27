#ifndef TEXTURA_H
#define TEXTURA_H

#include <QImage>
#include <QColor>

#include <string>
#include <iostream>
#include "glm/glm.hpp"

using namespace glm;

using namespace std;

class Texture
{
  QImage image;

public:
    Texture(string nomfitxer);
    virtual ~Texture();

    vec3 getColorPixel(vec2 uv);

};

#endif // MATERIALTEXTURA_H
