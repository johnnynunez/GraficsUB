#include "Scene.h"
#include "stdlib.h"

Scene::Scene(){
}

Scene::~Scene()
{
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            if (dynamic_cast<Sphere*>(objects[i]))
                delete (Sphere *)(objects[i]);
            if(dynamic_cast<Triangle*>(objects[i]))
                delete(Triangle*)(objects[i]);
            if(dynamic_cast<Circle*>(objects[i]))
                delete(Circle*)(objects[i]);
            if(dynamic_cast<Cilindre*>(objects[i]))
                delete(Cilindre*)(objects[i]);
            if(dynamic_cast<BoundaryObject*>(objects[i]))
                delete(BoundaryObject*)(objects[i]);
            if (dynamic_cast<Plane*>(objects[i]))
                delete (Plane *)(objects[i]);
            if (dynamic_cast<FittedPlane*>(objects[i]))
                delete (FittedPlane *)(objects[i]);
            if (dynamic_cast<Cube*>(objects[i]))
                delete (Cube *)(objects[i]);
        }
    }

    for(unsigned int i = 0; i < lights.size(); ++i){
        if(lights[i]){
            if(dynamic_cast<LightPuntual*>(lights[i]))
                delete(LightPuntual*)(lights[i]);
            if(dynamic_cast<LightVolumetric*>(lights[i]))
                delete(LightVolumetric*)(lights[i]);
        }
    }
    delete cam;
}

void Scene::setColorMap(ColorMap *cm) {
    colorMap = cm;

    vec3 ka(0.1,0.1,0.1);
    vec3 ks(1,1,1);
    float refraction = 1.5f;
    int shine = 250;
    for(unsigned int i = 0; i < objects.size(); ++i){
        vec3 kd = cm->getColor(objects[i]->getData());
        Material *m = new Metal(ka,kd,ks,shine);
        objects[i]->setMaterial(m);
    }
}


bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {

    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig,
    // pero no en aquesta funcio.
    //Considerem que no hem trobat col*lisionat amb ningun objecte
    //Hem de crear un nou Hitinfo per poder actualitzar si hem trobat un objecte més próxim.
    bool h = false;
    float hit_min = t_max;
    HitInfo hitinfo;
    //Hit del suelo
    if(ground->hit(raig,t_min,t_max,hitinfo)){//comprovem si es el terra
        h = true;
        if(hitinfo.t < hit_min){
            hit_min = hitinfo.t;
            info = hitinfo;
        }
    }

    for(Object *o: objects){//comprovem si els objectes i ens quedem el hit de tminima
        if(o->hit(raig,t_min,t_max,hitinfo)){
            h = true;
            if(hitinfo.t < hit_min){
                hit_min = hitinfo.t;
                info = hitinfo;
            }
        }
    }
    return h;
}



vec3 Scene::ComputeColor (Ray &ray, int depth) {

    vec3 color;
    vec3 ray2;
    HitInfo hitInfo = HitInfo();
    bool hasOcurredHit = false;
    hasOcurredHit = hit(ray,EPSILON,1000,hitInfo);
    ray2 = -normalize(ray.direction);


    if(hasOcurredHit){
        //Si ha hagut una interseccio amb algun objecte calculara el raig d'ombra, cal calcular les seves components:
        //Obtenim el punt de la interseccio (P):
        vec3 punt = hitInfo.p;
        //Vector Normal del punt d'interseccio (N):
        vec3 N = hitInfo.normal;
        Ray scattered;
        vec3 c = vec3(0.0f);
        //Material del objecte que ens dona les seves components(Ka, Ks, Kd, shininess)
        const Material *material = hitInfo.mat_ptr;

        color += (vec3(1.f)-hitInfo.mat_ptr->Kt) * BlinnPhong(punt,N,material);

        if(MAX_DEPTH > depth) {
            if(hitInfo.mat_ptr->scatter(ray,hitInfo,c,scattered)) {
                color += hitInfo.mat_ptr->Kdiffuse*ComputeColor(scattered,depth+1)*c;
            }
        }
        // finalment fem la suma del sumatori amb la iluminacio global de l'escena:
        color += Iglobal * material->Kambient;

    }
    else{//En caso de no haber un hit establecemos el fondo, no antes que si no se satura el color al hacer recursiones.
        vec3 white = vec3(1.0,1.0,1.0);
        vec3 blue = vec3(0.5,0.7,1.0);
        float t = 0.5f*(ray2.y+1);
        color = vec3(t*blue+(1-t)*white);
    }

    return color;
}

vec3 Scene::ComputeLight(vec3 point, vec3 normal, const Material *material, Light *li){

    //Vector entre el punt P i la llum (L):
    vec3 L = normalize(li->position-point);
    vec3 V = normalize(cam->origin-point);
    //Vector mig normalitzat entre el vector de llum (L) i el vector del raig intersector (V), V és el ray2, obtenim H:
    vec3 H = normalize(L+V);

    //Definim un Ray per poder fel el hit (seguiria el vecotr L)
    Ray r_light(point, L);

    //Distancia entre la interseccio i la llum, sera el t_max:
    float distance = glm::distance(li->position, point);
    //CAlculem la atenuacio tal i com es diu en la part activitats del enunciat (0.5+0.01d²):
    li->atenuation = pow(li->a*distance,2) + li->b*distance + li->c;
    //Definim un hit info per el raig de llum.
    HitInfo* hitLight = new HitInfo();

    vec3 ambient = li->ambient*material->Kambient;

    vec2 uv = getUVPoint(point); //Calculem el punt en el espai UV.
    //Obtenim la difusa corresponents (tèxtel en cas de MaterialTextura).
    vec3 diffuse = li->diffuse * material->getDiffuse(uv) * glm::max(dot(L,normal),0.0f);

    vec3 specular = li->specular * material->Kspecular * vec3(pow(glm::max(dot(normal,H),0.0f),material->shininess));
    if(hit(r_light, EPSILON, distance, *hitLight)){
            //Si hi ha una interseccio entre el punt P i la llum, hi ha un objecte i es
            //calcula el color amb la següent formula: SUMATORI = ka * Ia

            //Quan dona ombra la part de la llum directa no arriba al objecte, es per
            //aixo que nomes ens interesa calcular la llum ambient (Ia*Ka)
        return ambient;
    }
    else{
            //En cas de que no hi hagi cap objecte en mig del raig, en el sumatori entren
            //totes les llums, directes (Id,Kd,Is,Ks) com indirectes (Ia,Ka), la formula
        //quedaria tal que aixi: SUMATORI = ((1.0/Atenuacio)*(kd*Id*(L·N) + ks*Is*(N·H)β)) + Ia*Ka
        return (diffuse + specular)/vec3(li->atenuation) + ambient;
    }
}

vec3 Scene::BlinnPhong(vec3 point, vec3 normal, const Material* material){
    //Sumatori del Blinn-Phong
    vec3 sum_light(0.0f);

    //Iterem cada llum per calcular el sumatori:
    //I = IaGlobal * Ka + SUMATORI((1.0/Atenuacio)*(kd*Id*(L·N) + ks*Is*(N·H )β)) + Ia*Ka)
    for(Light *li: lights){
        if(dynamic_cast<LightVolumetric*>(li)){
            for(Light *l: dynamic_cast<LightVolumetric*>(li)->composition){
                sum_light += ComputeLight(point, normal, material, l);
            }
        }
        else {
            //Calcul de la llum (Esencialment el Blinn-Phong)
            sum_light += ComputeLight(point, normal, material, li);
        }
    }
    //sum_light = (Iglobal*material->Kambient) + sum_light;

    return sum_light;
}

vec2 Scene::getUVPoint(vec3 point){
    //Aplicar Operació (extreta de Parcial Transpas)
    //xUV = xDades * ( xmaxUV - xminUV) /(xmax - xmin) - xmin * ( xmaxUV - xminUV) /(xmax - xmin) + xminUV
    float u = point.x /(DIM_SCENE[0][1] - DIM_SCENE[0][0]) - DIM_SCENE[0][0] /(DIM_SCENE[0][1] - DIM_SCENE[0][0]);
    float v = point.z /(DIM_SCENE[2][1] - DIM_SCENE[2][0]) - DIM_SCENE[2][0] /(DIM_SCENE[2][1] - DIM_SCENE[2][0]);
    return vec2(u,v);
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_cast<Animable*>(objects[i]) ) objects[i]->update(nframe);
    }
}

