#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {


    cout << "Init..." <<endl;

    Controller *controller = new Controller(RenderFactory::TEMPORAL, SceneFactory::TEMPORAL, ObjectFactory::SPHERE);

    controller->start(argc, argv);


    return(0);
}
