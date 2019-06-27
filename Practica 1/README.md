GiV - P1 Raytracing data Visualization
----------  

- [Yuse](https://github.com/Yusepp) 
- [Xavier](https://github.com/XavierMacias)
- [Gerard](https://github.com/gerardPuch) 
- [Johnny](https://github.com/johnnync13) 

Abstract

- En esta Primera práctica hemos trabajado el Algoritmo del Raytracing para la visualización de Datos. Para ello hemos utilizado diferentes técnicas de iluminación, reflexión y similares. Concretamente:

    - La fase 1 basada en la creación y visualización de superfícies geométricas usando las ecuaciones que las definen. Hemos creado           Triángulo,Cilindro y Boundary Object(mesh de Triángulos).
    - La fase 2 centrada en la iluminación(cálculo del color) de la escena usando la aproximación de Blinn-Phong así como la creación de       materiales con comportamientos Lambertianos,Metálicos y Transparentes. Todo esto modela fenómenos como la reflexión,la reflexión y       el sombreado.
    - La fase 3 que termina con la creación de un último material Textura que permite aplicar una textura encima de una superfície,           creando una dimensión alternativa UV con la cual obtener a cada parte de la superfície que trozo de textura le corresponde. Todo         esto es añadido mediante el Blinn-Phong. Por último tenemos la inclusión de series temporales que permiten crear animaciones.

Features


- Figures
    - [ ] Triangle - Johnny
    - [ ] Cilynder - Gerard/Yuse
    - [ ] Boundary Object - Xavier
- Blinn-Phong
    - [ ] Light - Gerard
    - [ ] Basic Blinn-Phong - Gerard/Johnny/Xavier/Yuse
    - [ ] Recursive Blinn-Phong - Gerard/Johnny/Xavier/Yuse
- Material
    - [ ] Metal - Yuse/Xavier
    - [ ] Transparent - Yuse/Johnny
    - [ ] Texture Gerard/Yuse/Xavier
- Animaciones
    - [ ] aplicaTG i escenas Gerard/Johnny/Xavier/Yuse


Extensions
- Antialiasing con varios Samplings de cada pixel(x16)


Screenshots
- [Metal Reflexiones sin AA](https://i.imgur.com/Ux1Ge82.jpg) 
- [Metal Reflexiones con AA](https://i.imgur.com/azXGb7h.jpg) 
- [Metal Reflexiones con AA grande](https://i.imgur.com/brx8ziK.jpg)
- [Escena Lambertian, Metal y Transparente](https://i.imgur.com/dtarpKD.jpg)
- [Escena DadesEuropa.txt](https://i.imgur.com/vhKoJdd.jpg)
- [Animación Crecimineto esfera](https://i.imgur.com/YL44X5h.mp4)
- [BoundaryObject básico](https://i.imgur.com/Otq5f7U.jpg)
- [Penombres i llums volumètricques](https://i.imgur.com/Otq5f7U.jpg)



 Additional Information
- Durante toda la práctica hemos seguido un ritmo constante y distribuido el trabajo entre varios miembros del grupo pero tambien       ayudandonos mutuamente. El primer obstáculo contra el que chocamos fue la visualización del Cilindro que tras mucha dedicación logramos realizar. Durante la creación de los materiales Transparentes y Metálicos así como el uso del Blinn-Phong de estos rehicimos el código varias veces hasta dar con la versión que funcionaba probando diferentes ideas. Las Texturas a priori iban pero se visualizaban mal y no entendíamos porque y a golpe de debug notamos que algo fallaba en el FittedPlane en su hit y logramos corregirlo haciendo asi la visualización de la textura correctamente. Por último los mas engorroso de todo nos ha resultado las animaciones que finalmente hemos logrado en base al código de ejemplo
