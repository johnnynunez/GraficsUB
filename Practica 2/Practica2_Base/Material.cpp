#include "Material.h"


Material::Material() {
    this->Kd = vec4(0.8,0.5,0.5,1.0);
    this->Ks = vec4(1.0,1.0,1.0,1.0);
    this->Ka = vec4(0.2,0.2,0.2,1.0);
    this->shine = 20;
}

Material::Material(vec4 Kd,vec4 Ks,vec4 Ka,float shine) {
    this->Kd = Kd;
    this->Ks = Ks;
    this->Ka = Ka;
    this->shine = shine;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(QGLShaderProgram *program){

    struct{
        GLuint kd_id;
        GLuint ks_id;
        GLuint ka_id;
        GLuint shine_id;
    }components_id;


    components_id.kd_id = program->uniformLocation("material.kd");
    components_id.ks_id = program->uniformLocation("material.ks");
    components_id.ka_id = program->uniformLocation("material.ka");
    components_id.shine_id = program->uniformLocation("material.shine");

    glUniform4fv(components_id.kd_id,1,Kd);
    glUniform4fv(components_id.ks_id,1,Ks);
    glUniform4fv(components_id.ka_id,1,Ka);
    glUniform1f(components_id.shine_id,shine);


}

