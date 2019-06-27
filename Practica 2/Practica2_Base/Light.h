#ifndef Light_H
#define Light_H

#include "./library/Common.h"
#include <QGLShaderProgram>

// Tipus de Lights
enum LightType : int {PUNTUAL = 0, DIRECTIONAL = 1, SPOTLIGHT = 2};

// Classe que representa els atributs d'una Light
// TO DO: A la fase 1 has d'incloure els atributs necessaris per codificar una llum

class Light {
    public:
        Light();
        Light(vec4 position);
        Light(LightType t,vec4 position,vec3 Is,vec3 Ia,vec3 Id,vec3 coeficients);
        Light(LightType t,vec4 position,vec3 Is,vec3 Ia,vec3 Id,vec3 coeficients, vec4 direction);
        Light(LightType t,vec4 position,vec3 Is,vec3 Ia,vec3 Id,vec3 coeficients, vec4 direction, float angle);

        vec4 getLightPosition();
        void setLightPosition(vec4 v);

        vec4 getLightDirection();
        void setLightDirection(vec4 v);

        vec3 getIa() const;
        void setIa(const vec3 &value);

        float getAngle();
        void setAngle(float a);

        float getSpotExp();
        void setSpotExp(float a);

        vec3 getId();
        void setId(vec3 i);

        vec3 getIs() const;
        void setIs(const vec3 &value);

        vec3 getCoeficients() const;
        void setCoeficients(const vec3 &value);

        LightType getTipusLight() const;
        void setTipusLight(const LightType &value);

        void lightToGPU(QGLShaderProgram *program, int index);

        vec3 Is,Ia,Id,coeficients;
        vec4 position, direction;
        LightType type;
        float angle, spotExponent;
        int MAX = 7;
};

#endif // Light_H
