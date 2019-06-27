#include "Camera.h"


Camera::Camera(vec4 lookfrom, vec4 lookat, vec4 vup, float vfov, int viewX, int viewY) { // vfov is top to bottom in degrees
    float aspect = float(viewX)/float(viewY);
    vp.pmin = vec2( 0., 0.);
    vp.a = viewX;
    vp.h = viewY;

    vfovRadians = vfov RAD;

    angX = 0;
    angY = 0;
    angZ = 0;

    float half_height = tan(vfovRadians/2);
    float half_width = aspect * half_height;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    vrp = lookat;
    distancia = length(origin - vrp);
    vUp = vup;

    window.pmin = vec2(-half_width, -half_height);
    window.a = 2*half_width;
    window.h = 2*half_height;

    dant = 0.01;
    dpost = 200;

    typeProjection = PARALLELA;
    CalculaModelView();
    CalculaProjection();

}

Camera::Camera(int width, int height)
{
    origin = vec4(0.0, 0.0, 10.0, 1.0);

    angX = 0;
    angY = 0;
    angZ = 0;

    vp.a = width;
    vp.h = height;
    vp.pmin[0] = 0;
    vp.pmin[1] = 0;

    float half_height = 1.0;
    float half_width = 1.0;

    vrp = vec4( 0.0, 0.0, 0.0, 1.0);
    distancia = length(origin -vrp);

    w = vec4(0.0, 0.0, 1.0, 0.0);
    vUp = vec4(0.0, 1.0, 0.0, 0.0);
    u = normalize(cross(vUp, w));
    v = cross(w, u);

    window.pmin = vec2(-half_width, -half_height);
    window.a = 2*half_width;
    window.h = 2*half_height;

    dant = 0.01;
    dpost = 100;

    vfovRadians = 90.0 RAD;

    typeProjection = PARALLELA;
    CalculaModelView();
    CalculaProjection();
}

void Camera::init(int a, int h, Capsa3D capsaMinima)
{
    vec3 p1;
    float d;

    d = length (origin - vrp);
    p1[0] = capsaMinima.pmin[0]+capsaMinima.a;
    p1[1] = capsaMinima.pmin[1]+capsaMinima.h;
    p1[2] = capsaMinima.pmin[2]+capsaMinima.p;

    // Calcul del vrp com el centre de la capsa minima contenedora 3D
    vrp[0] = capsaMinima.pmin[0]+p1[0]/2.0;
    vrp[1] = capsaMinima.pmin[1]+p1[1]/2.0;
    vrp[2] = capsaMinima.pmin[2]+p1[2]/2.0;
    vrp[3] = 1.0;

    origin = vrp + w * length (p1-capsaMinima.pmin);

    distancia = length(origin -vrp);
    vfovRadians = 90.0 RAD;
    // Viewport
    vp.a = a;
    vp.h = h;
    vp.pmin[0] = 0;
    vp.pmin[1] = 0;

    dant = 0.01;
    dpost = 100;

    // Window

    CalculaModelView();

    CalculaWindow(capsaMinima);

    CalculaProjection();

}

void Camera::actualitzaCamera(Capsa3D capsaMinima) {
    vec3 p1;
    // Calcul del vrp com el centre de la capsa minima contenedora 3D
    p1[0] = capsaMinima.pmin[0]+capsaMinima.a;
    p1[1] = capsaMinima.pmin[1]+capsaMinima.h;
    p1[2] = capsaMinima.pmin[2]+capsaMinima.p;

    // Calcul del vrp com el centre de la capsa minima contenedora 3D
    vrp[0] = (capsaMinima.pmin[0]+p1[0])/2.0;
    vrp[1] = (capsaMinima.pmin[1]+p1[1])/2.0;
    vrp[2] = (capsaMinima.pmin[2]+p1[2])/2.0;
    vrp[3] = 1.0;

    origin = vrp + w * length (p1-capsaMinima.pmin);
    distancia = length(origin -vrp);

    CalculaModelView();

    CalculaWindow(capsaMinima);

    CalculaProjection();

}

void Camera::setFrustum(float vfov, float dant, float dpost) {
    float aspect = float(vp.a)/float(vp.h);

    vfovRadians = vfov RAD;
    float half_height = tan(vfovRadians/2);
    float half_width = aspect * half_height;

    window.pmin = vec2(-half_width, -half_height);
    window.a = 2*half_width;
    window.h = 2*half_height;

    this->dant = dant;
    this->dpost = dpost;

    typeProjection = PARALLELA;
    CalculaProjection();

}

void Camera::setObservador(vec4 lookfrom, vec4 lookat, vec4 vup) {


    w = normalize(lookfrom - lookat);

    w[3] = 0.0;
    u = normalize(cross(vup, w));
    u[3] = 0.0;
    v = normalize(cross(w, u));
    v[3] = 0.0;

    origin = lookfrom;
    vrp = lookat;
    vUp = vup;
    distancia = length(origin-vrp);

    CalculaModelView();

}

/* Nomes es crida aquest metode si han canviat els angles */
void Camera::rotaCamera() {

    vec3 angles((int)(angX)%360, (int)(angY)%360, (int)(angZ)%360);
    anglesToAxis(angles);

    origin = vrp + distancia*w;

    CalculaModelView();
}

//   Calcul del observador:
//   obs es el vrp translladat en la direccio del vector de visio  d'una
//   distancia d = distancia (obs, vrp) si la projeccio es perspectiva
//   i d'una distancia prou gran si la projeccio es paral.lela

vec4 Camera::CalculObs(vec4 vrp, double d, double angx, double angy)
{
 vec4 obs2;
 vec3 v;
 double norma;

 /* Calcul del vector de visio a partir dels angles */

 v[0] = sin (angy RAD) * cos (angx RAD);
 v[2] = cos (angy RAD) * cos (angx RAD);
 v[1]= - sin (angx RAD);

 norma = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

 v[0] = v[0]/norma;
 v[1] = v[1]/norma;
 v[2] = v[2]/norma;


 obs2[0] = vrp[0] + v[0] *d;
 obs2[1] = vrp[1] + v[1] *d;
 obs2[2] = vrp[2] + v[2] *d;
 obs2[3] = 1.0;

 return(obs2);

}

/* Pas a la GPU */

void Camera::toGPU(QGLShaderProgram *program)
{
    model_view = program->uniformLocation("model_view");
    projection = program->uniformLocation("projection");

    glUniformMatrix4fv( model_view, 1, GL_TRUE, modView );
    glUniformMatrix4fv( projection, 1, GL_TRUE, proj );

//    vec4 obser(CalculObs(vrp, distancia, angX, angY));

   GLuint glObservador = program->uniformLocation("obs");
   glUniform4fv(glObservador, 1, origin);
}

void Camera::setModelView(QGLShaderProgram *program, mat4 m)
{
    model_view = program->uniformLocation("model_view");
    glUniformMatrix4fv( model_view, 1, GL_TRUE, m);
 }

void Camera::setProjection(QGLShaderProgram *program, mat4 p)
{
    projection = program->uniformLocation("projection");
    glUniformMatrix4fv( projection, 1, GL_TRUE, p);
}

void Camera::setViewport(int x, int y, int a, int h)
{
    vp.pmin[0] = x;
    vp.pmin[1] = y;
    vp.a = a;
    vp.h = h;
}

// Suposa que les dades d'obs, vrp i vup son correctes en la camera

void Camera::CalculaModelView()
{
    modView = LookAt(origin, vrp, vUp);

}

void Camera::CalculaProjection()
{
    if (typeProjection==PARALLELA)
        proj = Ortho(window.pmin[0], window.pmin[0]+window.a, window.pmin[1], window.pmin[1]+window.h, dant, dpost );
    else
       proj = Frustum( window.pmin[0], window.pmin[0]+window.a, window.pmin[1], window.pmin[1]+window.h, dant, dpost );

}

///////////////////////////////////////////////////////////////////////////////
// convert Euler angles(x,y,z) to axis(side, up, forward)
// The order of rotation is Yaw->Pitch->Roll (Ry*Rx*Rz)
// Rx: rotation about X-axis, pitch
// Ry: rotation about Y-axis, yaw(heading)
// Rz: rotation about Z-axis, roll
//      Ry         Rx          Rz
// |Cy  0 -Sy| |1   0  0| | Cz Sz 0|   |CyCz-SySxSz  CySz+SySxCz  -SyCx|  <- side
// | 0  1   0|*|0  Cx Sx|*|-Sz Cz 0| = |-CxSz        CxCz         Sx   |  <- up
// |Sy  0  Cy| |0 -Sx Cx| |  0  0 1|   |SyCz+CySxSz  SySz-CySxCz  CyCx |  <- forward
///////////////////////////////////////////////////////////////////////////////
void Camera::anglesToAxis(vec3 angles)
{

    float sx, sy, sz, cx, cy, cz, theta;
    vec3 side, up, forward;

    theta = angles[0] RAD;
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = angles[1] RAD;

    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = angles[2] RAD;
    sz = sinf(theta);
    cz = cosf(theta);


    // determine side vector
   side[0] = cy*cz - sy*sx*sz;
    side[1] = cy*sz + sy*sx*cz;
    side[2] = -sy*cx;
    u = side;
    u.w = 0.0;

    // determine up vector
    up[0] = -cx*sz;
    up[1] = cx*cz;
    up[2] = sx;
    v = up;
    v.w = 0.0;

    // determine forward vector
    forward[0] = sy*cz + cy*sx*sz;
    forward[1] = sy*sz - cy*sx*cz;
    forward[2] = cy*cx;
    w = forward;
    w.w = 0.0;

    vUp = v;

}



void  Camera::AmpliaWindow(double r)
{
  // Pre r = 1.5 => amplia a 150%
  double na, da;

  na  = window.a * (1.0 + r);
  da = na - window.a;
  window.pmin[0] = window.pmin[0] - 0.5*da;
  window.a  = na;
  na  = window.h * (1.0 + r);
  da = na - window.h;
  window.pmin[1] = window.pmin[1] - 0.5*da;
  window.h  = na;

  AjustaAspectRatioWd();
  CalculaProjection();
}


// Metode de calcul de la window a partir de la capsa contenidora
void Camera::CalculaWindow( Capsa3D c)
{
    vec4  vaux[8], vaux2[8];
    vec4 vup = vec4(0.0, 1.0, 0.0, 0.0);
    int i;

    modView = LookAt(origin, vrp, vup);

     /* Passo els 8 vertexs de la capsa per MVIS */
    VertexCapsa3D(c, vaux);

   for(i=0; i<8; i++) {
        vaux2[i]= modView*vaux[i];
    }
    window = CapsaMinCont2DXYVert(vaux2, 8);

    AmpliaWindow(0.05);      /* marges del 20%  */

    vfovRadians = 2.0f* atan2(window.h/2.0, length(origin-vrp));

}



// Donat un window i un viewport, amplia el window per tal que el seu
// aspect ratio sigui igual al del viewport

void    Camera::AjustaAspectRatioWd()
{

    double arvp, arwd;

    arvp = ((double) vp.h)/((double)(vp.a));
    arwd = window.h/window.a;
    if(arwd > arvp) {
        window.a = window.h/arvp;
    }
    else if (arwd <arvp) {
        window.h = window.a *arvp;

    }
    window.pmin[0] = -0.5*window.a;
    window.pmin[1] = -0.5*window.h;
}



Capsa2D  Camera::CapsaMinCont2DXYVert( vec4 *v, int nv)
{
    Capsa2D c;
    vec2    pmin, pmax;
    int     i;

    pmin[0] = v[0][0];       pmin[1] = v[0][1];
    pmax[0] = v[0][0];       pmax[1] = v[0][1];
    for(i=1; i<nv; i++) {
      if(v[i][0] <pmin[0])
        pmin[0] = v[i][0];
      if(v[i][1] <pmin[1])
        pmin[1] = v[i][1];
      if(v[i][0] >pmax[0])
        pmax[0] = v[i][0];
      if(v[i][1] >pmax[1])
        pmax[1] = v[i][1];
    }

    c.a = pmax[0]-pmin[0];
    c.h = pmax[1]-pmin[1];
    c.pmin[0] = -c.a/2.0;
    c.pmin[1] = -c.h/2.0;
    return c;
}


void Camera::VertexCapsa3D(Capsa3D capsaMinima, vec4 vaux[8])
{
    vec3 ptfi;

    ptfi[0] = capsaMinima.pmin[0]+capsaMinima.a;
    ptfi[1] = capsaMinima.pmin[1]+capsaMinima.h;
    ptfi[2] = capsaMinima.pmin[2]+capsaMinima.p;

    vaux[0] = vec4(capsaMinima.pmin[0], capsaMinima.pmin[1], capsaMinima.pmin[2], 1.0);
    vaux[1] = vec4(capsaMinima.pmin[0], capsaMinima.pmin[1], ptfi[2], 1.0);
    vaux[2] = vec4(capsaMinima.pmin[0],  ptfi[1], capsaMinima.pmin[2],1.0);
    vaux[3] = vec4(capsaMinima.pmin[0], ptfi[1], ptfi[2], 1.0);
    vaux[4] = vec4(ptfi[0],capsaMinima.pmin[1], capsaMinima.pmin[2],1.0);
    vaux[5] = vec4(ptfi[0], capsaMinima.pmin[1], ptfi[2],1.0);
    vaux[6] = vec4(ptfi[0], ptfi[1], capsaMinima.pmin[2], 1.0);
    vaux[7] = vec4(ptfi[0], ptfi[1], ptfi[2], 1.0);
}
