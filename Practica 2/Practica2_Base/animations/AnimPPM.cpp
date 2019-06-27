#include "AnimPPM.h"

AnimPPM::AnimPPM(Scene *s) : RayTracingPPM (s)
{
}

AnimPPM::~AnimPPM()
{
    cleanup();
}

void AnimPPM::renderingScene(){

    string resultName;
    for (unsigned long i=0; i<MAXFRAMES; i++ ) {
        resultName = "resultat" + std::to_string(i) + ".ppm";
        RayTracingPPM::initRender(resultName);
        // update dels objectes de l'escena per a posar-los al seu lloc,
        // en el cas que tinguin animacions associades
        scene->update(i);
        // càlcul del frame concret
        rendering();
        myfile.close();
    }
    Render::exitRender();
}
