#include "Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t,vec4 position,vec3 Is,vec3 Ia,vec3 Id,vec3 coeficients, vec4 direction, float angle){
    setIa(Ia);
    setId(Id);
    setIs(Is);
    setTipusLight(t);
    setCoeficients(coeficients);
    setLightPosition(position);
    setLightDirection(direction);
    setAngle(angle);
    setSpotExp(1.0);
}

Light::Light(LightType t,vec4 position,vec3 Is,vec3 Ia,vec3 Id,vec3 coeficients, vec4 direction){
    setIa(Ia);
    setId(Id);
    setIs(Is);
    setTipusLight(t);
    setCoeficients(coeficients);
    setLightPosition(position);
    setLightDirection(direction);
    setAngle(15.0);
    setSpotExp(1.0);
}

Light::Light(LightType t,vec4 position,vec3 Is,vec3 Ia,vec3 Id,vec3 coeficients){
    setIa(Ia);
    setId(Id);
    setIs(Is);
    setTipusLight(t);
    setCoeficients(coeficients);
    setLightPosition(position);
    setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    setAngle(15.0);
    setSpotExp(1.0);
}

Light::Light(vec4 position){
    setIa(vec3(1.0,0.0,0.0));
    setId(vec3(0.0,1.0,0.0));
    setIs(vec3(0.0,0.0,1.0));
    setTipusLight(PUNTUAL);
    setCoeficients(vec3(0.0,0.0,1.0));
    setLightPosition(position);
    setLightDirection(vec4(0.0,-1.0,0.0,1.0));
    setAngle(15.0);
    setSpotExp(1.0);
}

Light::Light(){
    setIa(vec3(0.2));
    setId(vec3(0.8));
    setIs(vec3(1.0));
    setTipusLight(PUNTUAL);
    setCoeficients(vec3(0.0,0.0,1.0));
    setLightPosition(vec4(10.0,10.0,20.0,0.0));
    setLightDirection(vec4(0.0,1.0,0.0,1.0));
    setAngle(5.0);
    setSpotExp(1.0);
}


/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getId() {
   return Id;
}

/**
 * @brief Light::setId
 * @param i
 */
void Light::setId(vec3 i) {
    Id = i;

}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightPosition() {
    return position;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightPosition(vec4 v) {
    position = v;
}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightDirection() {
    return direction;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightDirection(vec4 d) {
    direction = d;
}

/**
 * @brief Light::getAngle
 */
float Light::getAngle() {
    return angle;
}

/**
 * @brief Light::setAngle
 * @param v
 */
void Light::setAngle(float a) {
    angle = a * (2.0*3.141592)/360.0;
}

/**
 * @brief Light::getSpotExp
 */
float Light::getSpotExp() {
    return spotExponent;
}

/**
 * @brief Light::setSpotExp
 * @param v
 */
void Light::setSpotExp(float exp) {
    spotExponent = exp;
}


/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
       return Ia;
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    Ia = value;
}

/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    return Is;
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    Is = value;
}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 Light::getCoeficients() const
{
    return coeficients;
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void Light::setCoeficients(const vec3 &value)
{
    coeficients = value;
}


/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const{
    return type;
}

/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value){
    type = value;
}

void Light::lightToGPU(QGLShaderProgram *program, int index){
    // 1. Es declara un vector d'identificadors
    struct gl_IdExemple
    {
        GLuint position_id;
        GLuint Is_id;
        GLuint Ia_id;
        GLuint Id_id;
        GLuint coeficients_id;
        GLuint direction_id;
        GLuint angle_id;
        GLuint sExp_id;
        GLuint type_id;
    };
    gl_IdExemple llum_components;

    llum_components.position_id = program->uniformLocation(QString("llum[%1].position").arg(index));
    llum_components.Is_id = program->uniformLocation(QString("llum[%1].Is").arg(index));
    llum_components.Ia_id = program->uniformLocation(QString("llum[%1].Ia").arg(index));
    llum_components.Id_id= program->uniformLocation(QString("llum[%1].Id").arg(index));
    llum_components.coeficients_id = program->uniformLocation(QString("llum[%1].coeficients").arg(index));
    llum_components.direction_id = program->uniformLocation(QString("llum[%1].direction").arg(index));
    llum_components.angle_id = program->uniformLocation(QString("llum[%1].angle").arg(index));
    llum_components.sExp_id = program->uniformLocation(QString("llum[%1].sExp").arg(index));
    llum_components.type_id = program->uniformLocation(QString("llum[%1].type").arg(index));

    // 3. Bind de les zones de memòria que corresponen
    glUniform4fv(llum_components.position_id,1,this->position);
    glUniform4fv(llum_components.Is_id,1,vec4(this->Is,1.0));
    glUniform4fv(llum_components.Ia_id,1,vec4(this->Ia,1.0));
    glUniform4fv(llum_components.Id_id,1,vec4(this->Id,1.0));
    glUniform3fv(llum_components.coeficients_id,1, this->coeficients);
    glUniform4fv(llum_components.direction_id,1, this->direction);
    glUniform1f(llum_components.angle_id, this->angle);
    glUniform1f(llum_components.sExp_id, this->spotExponent);
    glUniform1i(llum_components.type_id, this->type);
}
