GiV - P2 Métodos proyectivos
----------  

- [Yuse](https://github.com/Yusepp) 
- [Xavier](https://github.com/XavierMacias)
- [Gerard](https://github.com/gerardPuch) 
- [Johnny](https://github.com/johnnync13) 

    Este es el modelo base del README.rst que tendréis que añadir en el índice de vuestro **GitHub** y que os servirá como documentación de la práctica. De cara a la presentación de este documento borrad todas las notas y este texto.

Abstract
- En esta segunda práctica hemos trabajado el algoritmo del Z-Buffer para visualizar datos. Para eso hemos usado shaders (vertex shader i fragment shader) que permiten diferentes tipos de iluminación. Para hacerlo hemos pasado por dos fases distintas:

    - En la fase 1 definimos los materiales y las luces, para luego pasarlos a la GPU e implementar los dos tipos 	de shading: Gourand y Phong, a partir del algoritmo Blinn-Phong de la anterior práctica. El Gourand se 		define en el VertexShader y el Phong en el FragmentShader. También se incluyen texturas a la visualización 	del objeto cargado, y creamos un plano, para, de forma parecida a la práctica 1, leer datos y visualizar 		objetos a partir de un fichero txt.

	- En la fase 2 simplemente creamos animaciones de forma parecida a la práctica 1, y 		hacemos algunos ejercicios opcionales. 

Features
- Fase 1
    - Material - Yuse/Xavier
    - Light
        - [ ] Puntual - Xavier/Yuse/Gerard/Johnny
        - [ ] Direccional - Gerard 
        - [ ] (Opcional) Spotlight - Gerard  
        - [ ] Ambient Global - Xavier
    - Shading
        - [ ] Phong - Johnny/Gerard/Yuse/Xavier
        - [ ] Gouroud - Johnny/Gerard/Yuse/Xavier
        - [ ] (Opcional) Toon - Yuse
    - Textures
        - [ ] Textura com material - Gerard/Johnny/Yuse  
        - [ ] Mapping indirecte - Johnny

- Fase 2 
    - [ ] Animacions amb dades temporals/TG - Yuse
    - [ ] Normal mapping - Johnny
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [ ] Transparencias via objectes (solo shaders) - Johnny 
    - [ ] Transparencias via environmental mapping.


Extensions
Hemos creado un botón en el menú para poder mostrar el mapping indirecto directamente.

Screenshots
- [Gourand con una luz puntual](https://imgur.com/azQnprM)
- [Toon shading con una luz puntual](https://imgur.com/xYRp2l3)
- [Phong con una luz direccional](https://imgur.com/1BDolma)
- [Phong con 3 luces (puntual, direccional y spotlight)](https://imgur.com/pSxvds5) 
- [Objeto con textura](https://imgur.com/azQnprM)
- [Bump Mapping](https://imgur.com/S5eQyWm)
- [Animació](https://imgur.com/mz5JAVo)

Additional Information
- Durante toda la práctica hemos seguido un ritmo constante y hemos distribuido el trabajo entre varios miembros del grupo, pero también ayudándonos mutuamente. El primer obstáculo contra el que chocamos fue la visualización de las texturas, ya que tanto el material como las luces lo conseguimos con relativa facilidad. Las Texturas a priori iban pero teníamos mal implementado el algoritmo toGPU de la textura. Las animaciones no suponieron demasiado problema. Por último, en cuanto a los opcionales, hemos conseguido realizar el mapping indirecto y las luces, pero tuvimos problemas con los siguientes algoritmos:
1. El algoritmo para objetos sin textura.
2. En el Bump Mapping (normal mapping) no hemos realizado el cálculo de la tangente, para que si obtenemos un plano, sus normales sean distintas. Por ejemplo una textura de ladrillos.
3. Las transparencias hemos implementado el código y los shaders, pero no hemos conseguido que se vea bien la transparencia.
4. En el Environmental Mapping no hemos puesto el código en el GitHub, pero hemos conseguido realizar el código de la teoria, visualizándose el cubo. Pero no hemos conseguido que se visualizasen los reflejos. Por lo tanto lo hemos quitado porque hacía que el programa se cerrara.
