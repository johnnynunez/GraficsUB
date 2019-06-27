#include "plane.h"

Plane::Plane(vec4 v1, vec4 v2, vec4 v3, vec4 v4):Object (6){

    this->points[0] = v1;
    this->points[1] = v2;
    this->points[2] = v3;
    this->points[3] = v2;
    this->points[4] = v3;
    this->points[5] = v4;
    this->normals[0] = vec4(0,1,0,1);
    this->normals[1] = vec4(0,1,0,1);
    this->normals[2] = vec4(0,1,0,1);
    this->normals[3] = vec4(0,1,0,1);
    this->normals[4] = vec4(0,1,0,1);
    this->normals[5] = vec4(0,1,0,1);
    this->textCoord[0] = vec2(0,0);
    this->textCoord[1] = vec2(1,0);
    this->textCoord[2] = vec2(0,1);
    this->textCoord[3] = vec2(1,0);
    this->textCoord[4] = vec2(0,1);
    this->textCoord[5] = vec2(1,1);
    this->mat = new Material();

}

Plane::~Plane(){

}
void Plane::toGPU(QGLShaderProgram *pr){
    qDebug() << "Plane to GPU.....";
    program = pr;
    // Creació d'un vertex array object
    glGenVertexArrays(1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer);

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );
    toGPUTexture(program);
}
void Plane::toGPUTexture(QGLShaderProgram *pr){
    program = pr;

    // TO DO: Cal implementar en la fase 1 de la practica 2
    // S'ha d'activar la textura i es passa a la GPU
    qDebug() << "ObjectTextura to GPU...\n";

    program = pr;
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );


}

void Plane::draw(){
    //texture->bind(0);
    drawTexture();
    mat->toGPU(program);

    // Creació d'un vertex array object

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object

    //Se repite el paso de datos por si hay mas de un objeto
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    //Seleccionamos la zona del buffer peara copiar los datos
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*6 + sizeof(point4)*6+ sizeof(vec2)*6, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*6, points);
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*6, sizeof(point4)*6, normals );

    //textura coordenadas
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*6+sizeof(point4)*6, sizeof(vec2)*6, textCoord);

    // set up vertex arrays
    glBindVertexArray( vao );

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*6));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  (void*)((sizeof(point4)*6)+sizeof (point4)*6));
    glEnableVertexAttribArray(2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, 4 );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);


}

void Plane::drawTexture(){

    // TO DO: Cal implementar en la fase 1 de la practica 2
    // S'ha d'activar la textura i es passa a la GPU

    // S'activa la textura i es passa a la GPU
    program->setUniformValue("mytexture",0);


}

void Plane::setTexture(QOpenGLTexture *t){
    texture = t;
}

void Plane::aplicaTG(TG *tg){

}
