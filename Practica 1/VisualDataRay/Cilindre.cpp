#include "Cilindre.h"

Cilindre::Cilindre(vec3 center,float radi,float h):Object(h){
    this->center = vec3(0.0,0.0,0.0);
    this->radi = 1;
    this->high = 1;
    this->n1 = vec3(0.0,1.0,0.0);
    this->n2 = vec3(0.0,-1.0,0.0);
    this->top1 = new Circle(n1,this->center.y+vec3(0,high,0), 1);
    this->top2 = new Circle(n2,this->center,1);


}

Cilindre::~Cilindre(){//eliminem els cercles creats
    delete top1;
    delete top2;
}

bool Cilindre::cilindreHit(const Ray& r, float t_min, float t_max, HitInfo& info) const{
    //comprovem si hit amb el cos principal del cilindre
    //Calculem x² + z² = 1, on x = p0x + vx*t z = x = p0z + vz*t components del raig
    //Resolent per t podem obtenir una equacio de 2n grau format at² + bt + c = 0 on:
    //a = vx² + vz²
    float a = (r.dirVector().x * r.dirVector().x) + (r.dirVector().z * r.dirVector().z);
    if(a < EPSILON){//no té solució real no hi ha intersecció
        return false;
    }
    //b = 2*(vx*(p0x - cx) + (vz*(p0z - cz))
    float b = 2*(r.dirVector().x * (r.initialPoint().x - center.x) +
                 r.dirVector().z * (r.initialPoint().z - center.z));
    //c = (pox - cx)² + (poz - cz)² - 1
    float c = ((r.initialPoint().x - center.x)*(r.initialPoint().x - center.x)) +
            ((r.initialPoint().z - center.z)*(r.initialPoint().z - center.z)) - 1;

    //Pero comprovant el resultat de l'arrel ja podem treure conclusions i estalviar calculs

    float discrim = (b * b) - (4 * a * c);
    float t1,t2;//dos posibles t que segueixen (-b +- SQRT(b² – 4 * a * c) ) / (2 * a)
    if(discrim < EPSILON){//no té solució real no hi ha intersecció
        return false;
    }
    else if(discrim > 0-EPSILON && discrim < 0+EPSILON){//Raig tangent al cilindre 1 únic t
        t1 = t2 = -b / (2 * a);//no tenim arrel
    }
    else{//Tenim 2 interseccions i hem d'agafar la t més petita
        t1 = (-b + sqrtf(discrim))/(2 * a);
        t2 = (-b - sqrtf(discrim))/(2 * a);
    }
    if(t2 < t1 && t2 >= 0){//ens quedem la t més petita.
        t1 = t2;
    }
    if(t1 < 0){
        return false;

    }
    if(t1 < t_max+EPSILON && t1 > t_min-EPSILON){
        //Calculem les coordenades del punt d'intersecció.
        vec3 t = r.pointAtParameter(t1);
        //Si la intersecció és més petita que l'alçada, es troba dins
        //del nostre cilindre.CILINDRE
        if(t.y < center.y+high+EPSILON && t.y > center.y-EPSILON){
            //omplim info
            info.t = t1;
            info.p = r.pointAtParameter(info.t);
            info.normal = (info.p - center)/radi;
            info.mat_ptr = material;
            return true;
        }
    }

    return false;
}

bool Cilindre::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    bool hasHit = false;
    float t_cilindre(std::numeric_limits<float>::infinity());
    float t_top1(std::numeric_limits<float>::infinity());
    float t_top2(std::numeric_limits<float>::infinity());

    //CALCUL INTERSECCIÓ AMB CILINDRE (t_cilindre)
    if(cilindreHit(r,t_min,t_max,info)){
        t_top1 = info.t;
        hasHit = true;
    }
    //CALCUL INTERSECCIÓ AMB TOP1 (t_top1)
    if(top1->hit(r,t_min,t_max,info)){
        t_top1 = info.t;
        hasHit = true;
    }
    //CALCUL INTERSECCIÓ AMB TOP2 (t_top2)
    if(top2->hit(r,t_min,t_max,info)){
        t_top2 = info.t;
        hasHit = true;
    }
    if(hasHit){
        float temp(std::numeric_limits<float>::infinity());
        if(t_cilindre < temp){//trobem quina es la intersecció minima
            temp = t_cilindre;
        }
        if(t_top1 < temp){
            temp = t_top1;
        }
        if(t_top2 < temp){
            temp = t_top2;
        }
        //omplim info
        info.t = temp;
        info.p = r.pointAtParameter(info.t);
        info.normal = vec3(info.p.x,0,info.p.z);
        info.mat_ptr = material;
    }
    return hasHit;
}

void Cilindre::aplicaTG(TG *t){
    vec4 c(center, 1.0);
    
    if (dynamic_cast<Translate *>(t)) {//desplacem el centre
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
    if (dynamic_cast<Scale *>(t)){//augmentem l'altura
        vec4 c(1.0,1.0,1.0,1.0);
        c = t->getTG() * c;
        this->high = c.x*high;
    }
    //reconstruim les tapes
    if(top1 != NULL){
        delete top1;
        top1 = new Circle(n1,this->center+vec3(0,high,0), 1);
    }
    if(top2 != NULL){
        delete top2;
        top2 = new Circle(n2,this->center,1);
    }
}
