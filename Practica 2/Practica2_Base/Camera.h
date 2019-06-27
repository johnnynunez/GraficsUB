/***************************************************/
/*           Definicio de la camera                */
/***************************************************/
#ifndef CAMERA_INCLOS
#define CAMERA_INCLOS

#include <iostream>
#include "./library/Common.h"
#include <QGLShaderProgram>



#define PI 3.141593

#define MAXDPOST 100000
#define MINDANT -100000
#define EPS 0.001

#define DEGREES *180.0/PI
#define RAD  *PI/180.0

typedef enum {PARALLELA = 0, PERSPECTIVA = 1} TipProj; 


/* =================================== */
/* =                                 = */
/* =             Camera              = */
/* =                                 = */
/* =================================== */

class Camera
{
public:
    explicit Camera(int width, int height);

    Camera(vec4 lookfrom, vec4 lookat, vec4 vup, float vfov, int viewX, int viewY) ;
    ~Camera() {}

    void init(int a, int h, Capsa3D c);

    void actualitzaCamera(Capsa3D capsaMinima);
    void rotaCamera();
    void setFrustum(float vfov, float dant, float dpost);
    void setObservador(vec4 lookfrom, vec4 lookat, vec4 vup);
    void toGPU(QGLShaderProgram *program);


    void CalculaModelView();
    void CalculaProjection();
    void CalculaWindow(Capsa3D);
    vec4 CalculObs(vec4 vrp, double d, double angx, double angy);

    void AjustaAspectRatioWd();
    void AmpliaWindow(double r);

    void anglesToAxis(vec3 angles);

    Capsa2D  CapsaMinCont2DXYVert( vec4 *v, int nv);

    void setViewport(int x, int y, int a, int h);
    void setModelView(QGLShaderProgram *program, mat4 m);
    void setProjection(QGLShaderProgram *program, mat4 p);

    vec4 origin;
    vec4 vrp;
    vec4 vUp;
    float distancia; // Distancia de l'origin a vrp
    double angX; // Angles de rotacio de la camera
    double angY;
    double angZ;
    vec4   u, v, w; // sistema de referencia de la camera

    TipProj typeProjection;
    // Plans de clipping anterior i posterior
    float dant, dpost;

    // window
    Capsa2D window;
    float vfovRadians;

    // Viewport
    Capsa2D vp;

private:
    void VertexCapsa3D(Capsa3D capsaMinima, vec4 vaux[8]);

    mat4  modView; // Matriu model-view de la CPU
    mat4  proj;  // Matriu projection de la CPU
    GLuint  model_view;  // model-view matrix uniform shader variable (GPU)
    GLuint  projection;  // projection matrix uniform shader variable (GPU)

};


#endif









