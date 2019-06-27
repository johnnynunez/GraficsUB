#include "Render.h"


void Render::setScene(Scene *s) {
    scene = s;
}

// Metode Render

// Aquesta funcio transforma cada pixel a coordenades de mon i
// envia un raig des de la camera en aquella direccio cridant al metode CastRay
// i pel pintar la imatge final:
// 1) Neteja la pantalla per a visualitzar el nou frame
// 2) Envia un raig a l'escena per a cada pixel de la pantalla i utilitza el color retornat per a pintar el pixel
// 3) Actualitza la sortida corresponent segons la implementació del mètode setPixelColor de cada fill

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

void Render::rendering() {
    // Recorregut de cada pixel de la imatge final
    for (int y = scene->cam->viewportY-1; y >= 0; y--) {
         for (int x = 0; x < scene->cam->viewportX; x++) {
            vec3 pixelColor(0, 0, 0);
            int samples = 16;
            for (int i = 0; i < samples;i++) {//MSAA(MultiSampling AntiAliasing) x16
                float u = float(x + drand48()) / float(scene->cam->viewportX);//16 mostres dels subpixels mes propers
                float v = float(y + drand48()) / float(scene->cam->viewportY);
                Ray r = scene->cam->getRay(u, v);
                vec3 subPixelColor = scene->ComputeColor(r,0);
                pixelColor += subPixelColor;
            }
            pixelColor /= vec3(samples);//calculem la mitja
            setPixelColor(pixelColor, x, y);//definim el color del pixel com la mitja dels subpixels

         }
    }
}

void Render::exitRender() {
    cleanup();
}

void Render::cleanup() {
    if (scene!=NULL)  delete scene;
}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void Render::startRendering(int argc, char **argv) {
    renderingScene();
}

void Render::renderingScene()  {
    initRender("resultat.ppm");
    rendering();
    exitRender();
}

