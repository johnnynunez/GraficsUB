#include <math.h>
#include <QtDebug>
#include <QString>
#include "GLWidget.h"
#include "./animations/Animation.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

    setFocusPolicy( Qt::StrongFocus );

}

GLWidget::GLWidget(const QGLFormat &glf, QWidget *parent) : QGLWidget(glf, parent) {

    setFocusPolicy( Qt::StrongFocus );
    scene = new Scene();
    scene->setCamera(new Camera(this->size().width(), this->size().height()));
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

GLWidget::~GLWidget() {
    makeCurrent();
    delete scene;
}


void GLWidget::setScene(Scene *sc) {
    scene = sc;
    scene->setCamera(new Camera(this->size().width(), this->size().height()));
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

/* Interacció amb GL i inicialització de shaders */

/**
 * @brief GLWidget::initializeGL()
 */
void GLWidget::initializeGL() {
    initShadersGPU();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); //desactivar para transparencias
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);
    //activar para transparencias
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    program=programs[3];
    // Creacio d'una Light per apoder modificar el seus valors amb la interficie
    //Light *l = new Light(Puntual, vec4(0.0), vec3(1.0,0.0,0.0), vec3(0.0,1.0,0.0), vec3(0.0,0.0,1.0), vec3(1.0,1.0,1.0));
    Light *l = new Light();
    l->setTipusLight(SPOTLIGHT);
    l->setAngle(30.0);
    l->setLightPosition(vec4(0.0,10.0,0.0,1.0));
    l->setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    scene->addLight(l);

    /*Light *l1 = new Light();
    l1->setTipusLight(PUNTUAL);
    l1->setAngle(30.0);
    l1->setLightPosition(vec4(10.0,0.0,0.0,1.0));
    l1->setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    scene->addLight(l1);

    Light *l2 = new Light();
    l2->setTipusLight(PUNTUAL);
    l2->setAngle(30.0);
    l2->setLightPosition(vec4(0.0,0.0,10.0,1.0));
    l2->setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    scene->addLight(l2);
    scene->LightsToGPU(program);

    Light *l3 = new Light();
    l3->setTipusLight(DIRECTIONAL);
    l3->setLightDirection(vec4(0.0,1.0,0.0,1.0));
    scene->addLight(l3);*/

    scene->camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief GLWidget::paintGL()
 */
void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    scene->camera->toGPU(program);
    scene->draw();

}

/**
 * @brief GLWidget::resizeGL()
 */
void GLWidget::resizeGL(int width, int height) {

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    scene->camera->vp.a = width;
    scene->camera->vp.h = height;

    scene->camera->CalculaWindow(scene->capsaMinima);

    updateGL();
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    initShader("://resources/vshader1.glsl", "://resources/fshader1.glsl",0);
    initShader("://resources/vtoonshader.glsl","://resources/ftoonshader.glsl",1);
    initShader("://resources/vphongshader.glsl","://resources/fphongshader.glsl",2);
    initShader("://resources/vgouraudshader.glsl", "://resources/fgouraudshader.glsl",3);
    initShader("://resources/vphongshaderTex.glsl","://resources/fphongshaderTex.glsl",4);
    //initShader("://resources/vBackGroundshader.glsl","://resources/fBackGroundshader.glsl",5);
    initShader("://resources/vBumpshader.glsl","://resources/fBumpshader.glsl",6);
    initShader("://resources/vEnvironmentalshader.glsl","://resources/fEnvironmentalshader.glsl",7);
    initShader("://resources/vTransparencyshader.glsl","://resources/fTransparencyshader.glsl",8);
    initShader("://resources/vphongshaderTexIndirecte.glsl","://resources/fphongshaderTexIndirecte.glsl",9);

}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}

/**
 * @brief GLWidget::initShader()
 * Compila i linka el vertex i el fragment shader
 */
void GLWidget::initShader(const char* vShaderFile, const char* fShaderFile,int numprog){
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    programs[numprog] = new QGLShaderProgram(this);
    programs[numprog]->addShader(vshader);
    programs[numprog]->addShader(fshader);
    programs[numprog]->link();
    programs[numprog]->bind();
}

/** Gestio de les animacions i la gravació d'imatges ***/

void GLWidget::setCurrentFrame(){

    scene->update(currentFrame);
    updateGL();
    this->saveFrame();
    currentFrame++;

    if (currentFrame == MAXFRAMES)
        timer->stop();

}

void GLWidget::saveFrame(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentFrame).toString()+".jpg");
}

void GLWidget::saveImage(){

    this->grabFrameBuffer().save("screen_output_"+QVariant(currentImage).toString()+".jpg");
    currentImage++;
}



/** Metodes SLOTS que serveixen al builder per a actualitzar l'escena i els objectes */

void GLWidget::updateObject(Object *obj) {

    obj->toGPU(program);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::updateScene(Scene *sc) {
    // Control de la nova escena a la GPU

    scene = sc;
    scene->toGPU(program);

    // Podeu Utilitzar l'altre constructor de Camera
    // per inicialitzar els parametres de la camara.
    scene->setCamera(new Camera(this->size().width(), this->size().height()));
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();

}

/** Metodes que es criden des dels menús */

void GLWidget::saveAnimation() {
    // Comença el timer de l'animació
    timer = new QTimer(this);
    currentFrame=0;
    currentImage=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentFrame()));
    timer->start(1000);

}

void GLWidget::activaToonShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Toon";
    program = programs[1];

    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();
}

void GLWidget::activaPhongShader() {
    //Opcional: A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong";
    program = programs[2];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();

}

void GLWidget::activaGouraudShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Gouraud";
    program = programs[3];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();

}

void GLWidget::activaPhongTex() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong Tex";
    program = programs[4];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShaderTexture();
}

void GLWidget::activaBackground() {
    //A implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Background";
    program = programs[5];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();

}
void GLWidget::activaBumpMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Bump Mapping";
    program = programs[6];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();
}

void GLWidget::activaEnvMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Environmental Mapping";
    program = programs[7];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();
}

void GLWidget::activaTransparency() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Transparencia";
    program = programs[8];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);

    updateShader();
}

void GLWidget::activaPhongTexIndirecteShader() {
    //Opcional: A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong";
    program = programs[9];
    program->link(); // muntatge del shader en el pipeline grafic
    // per a ser usat
    program->bind(); // activació del shader al pipeline gràfic
    scene->toGPU(program);
    updateShader();

}

//Metode  per canviar de shaders.
void GLWidget::updateShader(){
    //A implementar a la fase 1 de la practica 2
    updateGL();
}

//Metode per canviar de shaders de textures
void GLWidget::updateShaderTexture(){
    //A implementar a la fase 1 de la practica 2
    updateGL();

}

/** Mètodes que es criden des de les finestres de dialeg */

void GLWidget::setRotation(float angle, float x, float y, float z)
{
    // Rotació en coordenades de mon que es farà sobre l'escena carregada

}
void GLWidget::setTranslation(float x, float y, float z)
{
    // Translació en coordenades de mon que es farà sobre l'escena carregada

}

void GLWidget::setScale(float s)
{
    // Escala en coordenades de mon que es  farà sobre l'escena carregada
}


void GLWidget::setPerspective(float verticalAngle, float nearPlane, float farPlane)
{
    scene->camera->setFrustum(verticalAngle, nearPlane, farPlane);

    updateGL();
}

void GLWidget::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    vec4 lookfrom(eye[0], eye[1], eye[2], 1.0);
    vec4 lookat(center[0], center[1], center[2], 1.0);
    vec4 vup(up[0], up[1], up[2], 1.0);
    scene->camera->setObservador(lookfrom, lookat, vup);

    updateGL();
}

void GLWidget::setLighting(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &coefs)
{
    vec4 lightPosition(lightPos[0],lightPos[1], lightPos[2], 1.0) ;
    vec3 intensityA( Ia[0], Ia[1], Ia[2]);
    vec3 intensityD( Id[0], Id[1], Id[2]);
    vec3 intensityS( Is[0], Is[1], Is[2]);

    scene->lights[0]->setIa(intensityA);
    scene->lights[0]->setId(intensityD);
    scene->lights[0]->setIs(intensityS);
    scene->lights[0]->setLightPosition(lightPosition);
    updateGL();
}

void GLWidget::setTextureFile(const QString &file)
{
    QOpenGLTexture *texture;

    texture = new QOpenGLTexture(QImage(file).mirrored());
    // TO DO: A modificar en la fase 1 de la practica 2
    // Per ara es posa la textura al primer objecte de l'escena

    for(int i=0;i<scene->elements.size();i++){
        scene->elements[i]->setTexture(texture);
    }
    activaPhongTex();
    updateShaderTexture();

}

/**  Mètodes d'interacció amb el ratolí */

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
            setXRotation(dy);
            setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
        // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
            Zoom(-1);
        else
            Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    if (angle >0) {
        scene->camera->angX += 5;
    } else if (angle<0)
        scene->camera->angX -= 5;
    qNormalizeAngle(scene->camera->angX);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    if (angle >0) {
        scene->camera->angY += 5;
    } else if (angle<0)
        scene->camera->angY-= 5;
    qNormalizeAngle(scene->camera->angY);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {
    scene->camera->AmpliaWindow(positiu*(0.005));

    emit FrustumCameraChanged(scene->camera);

    updateGL();
}
