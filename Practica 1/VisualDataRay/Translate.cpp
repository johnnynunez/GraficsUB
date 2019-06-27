#include "Translate.h"

Translate::Translate(glm::vec3 trasl): traslation(trasl)
{
    matTG = glm::translate(glm::mat4(1.0f), traslation);
}

Translate::~Translate()
{

}

