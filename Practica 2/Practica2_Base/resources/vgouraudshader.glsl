#version 330

#define PUNTUAL 0
#define DIRECTIONAL 1
#define SPOTLIGHT 2
#define MAX 4

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

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


out vec4 color;

void main(){
    float dist;
    float attenuation;
    vec4 diffuse;
    vec4 ambiental;
    vec4 specular;
    vec4 H;
    vec4 L;
    vec4 V;
    vec4 N = normalize(vNormal);
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    color = vec4(0.0,0.0,0.0,0.0);

    for(int i = 0; i < numl; i++){
        //Light l = llum[i];
        if(llum[i].type == 0) {
            dist = distance(vPosition.xyz,llum[i].position.xyz);
            attenuation = (1.0/(llum[i].coeficients.x*dist*dist + llum[i].coeficients.y * dist + llum[i].coeficients.z));
            L = normalize(llum[i].position - vPosition);
            V = normalize(obs - vPosition);
            H = normalize(L+V);
            diffuse = llum[i].Id * material.kd * max(dot(L,N),0.0);
            specular = llum[i].Is * material.ks * pow(max(dot(H,N),0.0),material.shine);
            ambiental = llum[i].Ia * material.ka;
            color += attenuation*(diffuse + specular) + ambiental;

            //color += vec4(1.0,0.0,0.0,1.0);
        } else if(llum[i].type == 1) {
            //Calculate BlinnPhong

            L = normalize(-llum[i].direction);
            V = normalize(obs - vPosition);
            H = normalize(L+V);
            diffuse = llum[i].Id * material.kd * max(dot(L,N),0.0);
            specular = llum[i].Is * material.ks * pow(max(dot(H,N),0.0),material.shine);
            ambiental = llum[i].Ia * material.ka;
            color += (diffuse + specular) + ambiental;

            //color += vec4(0.0,1.0,0.0,1.0);
        } else {//NO FUNCIONA NI AMB VALORS HARDCODED, HE DEIXAT EL CÀLCUL DE L'ATENUACIÓ, EN FUNCIÓ DEL SPOTEXPONENT DE LA LLUM SPOTLIGHT

            dist = distance(vPosition.xyz,llum[i].position.xyz);

            vec4  SL = normalize(-llum[i].direction);
            //vec4 SL = normalize(vec4(0.0,-1.0,0.0,1.0));
            //L = normalize(vec4(10.0,10.0,0.0,1.0) - vPosition);
            L = normalize(llum[i].position - vPosition);
            float spotEffect = pow(dot(SL,L),llum[i].sExp);

            attenuation = spotEffect / (llum[i].coeficients.x*dist*dist + llum[i].coeficients.y * dist + llum[i].coeficients.z);

            V = normalize(obs - vPosition);
            H = normalize(L+V);

            /*float a = dot(SL,L);
            a = abs(acos(a));
            a = a*(360/(2.0*3.141592));*/

            //color += vec4(a/360,a/360,a/360,1.0);
            /*if (cos(llum[i].angle) < dot(SL,L)){
                color += vec4(0.0,1.0,0.0,1.0);
            }*/
            if(dot(N,L) > 0){
                if (cos((10.0/2)*(2.0*3.141592)/360) > dot(SL,L)){
                //if(a < (llum[i].angle/2.0)){

                    diffuse = llum[i].Id * material.kd * max(dot(L,N),0.0);
                    specular = llum[i].Is * material.ks * pow(max(dot(H,N),0.0),material.shine);
                    ambiental = llum[i].Ia * material.ka;

                    color += attenuation*(diffuse + specular) + ambiental;
                    //color += vec4(0.0,1.0,0.0,1.0);
                }
            }
        }
    }

    color += AmbientGlobal * material.ka;
}
