#version 330

in vec4 fNormal;
in vec4 fPosition;

struct Components{
    vec4 kd;
    vec4 ks;
    vec4 ka;
    float shine;
};

struct Light{
    vec4 position;
    vec4 direction;
    vec4 Is;
    vec4 Ia;
    vec4 Id;
    vec3 coeficients;
    float angle;
    float sExp;
    int type;
};

uniform mat4 model_view;
uniform mat4 projection;
uniform Components material;
uniform Light llum[4];
uniform int numl;
uniform vec4 AmbientGlobal;
uniform vec4 obs;

out vec4 colorOut;

void main(){
    float dist;
    float attenuation;
    vec4 diffuse;
    vec4 ambiental;
    vec4 specular;
    vec4 H;
    vec4 L;
    vec4 V;
    vec4 N = normalize(fNormal);

    colorOut = vec4(0.0,0.0,0.0,0.0);

    for(int i = 0; i < numl; i++){
        if(llum[i].type == 0) {
            dist = distance(fPosition.xyz,llum[i].position.xyz);
            attenuation = (1.0/(llum[i].coeficients.x*dist*dist + llum[i].coeficients.y * dist + llum[i].coeficients.z));
            L = normalize(llum[i].position - fPosition);
            V = normalize(obs - fPosition);
            H = normalize(L+V);
            diffuse = llum[i].Id * material.kd * max(dot(L,N),0.0);
            specular = llum[i].Is * material.ks * pow(max(dot(H,N),0.0),material.shine);
            ambiental = llum[i].Ia * material.ka;
            colorOut += attenuation*(diffuse + specular) + ambiental;

            //colorOut += vec4(1.0,0.0,0.0,1.0);
        } else if(llum[i].type == 1) {
            //Calculate BlinnPhong

            L = normalize(-llum[i].direction);
            V = normalize(obs - fPosition);
            H = normalize(L+V);
            diffuse = llum[i].Id * material.kd * max(dot(L,N),0.0);
            specular = llum[i].Is * material.ks * pow(max(dot(H,N),0.0),material.shine);
            ambiental = llum[i].Ia * material.ka;
            colorOut += (diffuse + specular) + ambiental;

            //colorOut += vec4(0.0,1.0,0.0,1.0);
        } else { //BASAT EN LA FUNCIÓ DINS DE vgouraudshader.glsl NO ÉS SPOTLIGHT
            dist = distance(fPosition.xyz,llum[i].position.xyz);
            vec4  SL = normalize(-llum[i].direction);
            L = normalize(llum[i].position - fPosition);

            float spotEffect = pow(dot(SL,L),llum[i].sExp);
            attenuation = spotEffect / (llum[i].coeficients.x*dist*dist + llum[i].coeficients.y * dist + llum[i].coeficients.z);

            V = normalize(obs - fPosition);
            H = normalize(L+V);

            if(dot(N,L) > 0){
                if (cos((10.0/2)*(2.0*3.141592)/360) > dot(SL,L)){
                //if(a < (llum[i].angle/2.0)){

                    diffuse = llum[i].Id * material.kd * max(dot(L,N),0.0);
                    specular = llum[i].Is * material.ks * pow(max(dot(H,N),0.0),material.shine);
                    ambiental = llum[i].Ia * material.ka;

                    colorOut += attenuation*(diffuse + specular) + ambiental;
                    //colorOut += vec4(0.0,1.0,0.0,1.0);
                }
            }
        }
    }
    colorOut += AmbientGlobal * material.ka;
}
