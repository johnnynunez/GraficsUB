#version 330

in vec4 fNormal;
in vec4 fPosition;

out vec4 colorOut;

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
uniform Light llum[4];
uniform int numl;
uniform vec4 AmbientGlobal;

void main(){

    vec4 N;
    vec4 L;
    float intensity;

    colorOut = vec4(0.0,0.0,0.0,1.0);
    float div = numl;

    for(int i = 0; i < numl; i++){
        if(llum[i].type == 0) {
            N = normalize(fNormal);
            L = normalize(llum[i].position - fPosition);
            intensity = dot(N,L);
        }else if(llum[i].type == 1) {
            N = normalize(fNormal);
            L = normalize(-llum[i].direction);
            intensity = dot(N,L);
        }else{//BASAT EN LA FUNCIÓ DINS DE vgouraudshader.glsl NO ÉS SPOTLIGHT
            vec4  SL = normalize(-llum[i].direction);
            N = normalize(fNormal);
            L = normalize(llum[i].position - fPosition);
            if(dot(N,L) > 0){
                if (cos(llum[i].angle/2) > dot(SL,L)){
                    intensity = dot(N,L);
                }else intensity = 0.0;
            }else{
                intensity = 0.0;
            }

        }
        if(numl == 1) div = 2;

        if(intensity > 0.95){
            colorOut += vec4(0.9,0.5,0.5,1.0)/div;
        }
        if(intensity > 0.75){
            colorOut += vec4(0.8,0.4,0.4,1.0)/div;
        }
        if(intensity > 0.5){
            colorOut += vec4(0.6,0.3,0.3,1.0)/div;
        }
        if(intensity > 0.25){
            colorOut += vec4(0.4,0.2,0.2,1.0)/div;
        }
        else{
            colorOut += vec4(0.2,0.1,0.1,1.0)/div;
        }
    }
}

