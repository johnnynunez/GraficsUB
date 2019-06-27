#version 330
#define PI 3.141592
in vec4 fNormal;
in vec4 fPosition;
in vec2 fCoord;

out vec4 colorOut;

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
};

uniform mat4 model_view;
uniform mat4 projection;
uniform Components material;
uniform Light llum[7];
uniform vec4 AmbientGlobal;
uniform vec4 obs;
uniform sampler2D mytexture;
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
    vec4 color;
    vec4 tex=texture(mytexture,fCoord);
    if(tex.a < 0.1){
        discard;
    }
    else{
        color = tex * 0.5;
    }
    colorOut = color;
}
