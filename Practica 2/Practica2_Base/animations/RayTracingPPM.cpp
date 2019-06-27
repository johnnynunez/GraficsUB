
/* 
 * File:   RayTracing.cpp
 * Author: anna
 *
 * Created on 2 de enero de 2017, 19:43
 */


#include "RayTracingPPM.h"


using namespace std;

RayTracingPPM::RayTracingPPM(Scene *s) {
     setScene(s);
}

RayTracingPPM::~RayTracingPPM() {
     cleanup();
}

void RayTracingPPM::initRender(string nomFitxer) {
    // Les seguents linieas permeten escriure en un fitxer, el output
    myfile.open (nomFitxer);
    myfile<< "P3\n" << scene->cam->viewportX << " " << scene->cam->viewportY << "\n255\n";

//    std::ofstream out(nomFitxer);
//    std::streambuf *coutbuf = std::cout.rdbuf(); //salvar el buf antic
//    std::cout.rdbuf(out.rdbuf()); //redireccio de  std::cout al out.txt!
//    std::cout << "P3\n" << scene->cam->viewportX << " " << scene->cam->viewportY << "\n255\n";
}

void RayTracingPPM::setPixelColor(vec3 col, int x, int y) {
    // Aquestes tres linees permiten fer una sortida en un ppm per ser visualitzat per un gimp o similar
    int ir = int(255.99*col[0]);
    int ig = int(255.99*col[1]);
    int ib = int(255.99*col[2]);
    myfile << ir << " " << ig << " " << ib << "\n";
}

void RayTracingPPM::exitRender() {
    myfile.close();
    Render::exitRender();
}



