#include "Texture.h"

Texture::Texture(string nomfitxer)
{
 bool success = image.load(QString::fromStdString(nomfitxer));

 if (!success) std::cout << "Imatge no trobada" << endl;

}
Texture::~Texture() {

}
vec3 Texture::getColorPixel(vec2 uv) {
   QColor c(image.pixel((uv.x)*image.width(), (uv.y)*image.height() )); //row, col);
   return(vec3(c.redF(), c.greenF(), c.blueF()));
}
