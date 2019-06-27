#include "Cylinder.h"

Cylinder::Cylinder(vec3 cen, float r, float h):Object(h){
    this->center = cen;
    this->radius = r;
    this->high = h;

    vec3 n1(0.0,1.0,0.0);
    vec3 n2(0.0,-1.0,0.0);
    this->top1 = new Circle(n1, cen+vec3(0,h,0), r);
    this->top2 = new Circle(n2, cen, r);
}

bool Cylinder::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {
    //S'ha de fer el càlcul de les interseccions del cilindre i de les tapes.
    float t_c(std::numeric_limits<float>::infinity());
    float t_top1(std::numeric_limits<float>::infinity());
    float t_top2(std::numeric_limits<float>::infinity());
    bool hasHit = false;
    //La equació simplificada de la transició del raig en el cilindre és:
    //a*t²+b*t+c=0 (equació de segon grau).
    //Informació extreta de: https://inmensia.com/articulos/raytracing/cilindroycono.html
    //on a = dx'²+dz'²
    float a = (r.dirVector().x*r.dirVector().x)+(r.dirVector().z*r.dirVector().z);
    //on b = 2*(ox'*dx'+oz'*dz')
    float b = 2*(r.initialPoint().x*r.dirVector().x+r.initialPoint().z*r.dirVector().z);
    //on c = ox'²+oz'²
    float c = (r.initialPoint().x*r.initialPoint().x)+(r.initialPoint().z*r.initialPoint().z)-1;
    //calculem el determinant de l'equació.
    float det = b*b - 4*a*c;

    //si a és 0 o el determinant negatiu, l'equació no es pot resoldre.
    if((a < 0 || a > 0) && det >= 0){
        //poden haver-hi dos possibles interseccions: t1 i t2.
        float t1 = (-b-sqrt(det))/(det*2);
        float t2 = (-b+sqrt(det))/(det*2);

        //Les interseccions no ppoden ser negatives.
        if(!(t1 > 0 || t2 > 0)){
            //Comprovem quina intersecció és la més propera.
            float tmenor;
            if(t1 <= t2 && t1 >= 0){tmenor = t1;}
            if(t2 < t1 && t2 >= 0){tmenor = t2;}

            //Comprovem si el punt de intersecció entra dins dels límits establerts.
            if(tmenor >= t_max && tmenor <= t_min){
                //Calculem les coordenades del punt d'intersecció.
                float x = r.initialPoint().x + tmenor*r.dirVector().x;
                float y = r.initialPoint().y + tmenor*r.dirVector().y;
                float z = r.initialPoint().z + tmenor*r.dirVector().z;
                vec3 t(x,y,z);
                //Si la intersecció és més petita que l'alçada, es troba dins
                //del nostre cilindre.CILINDRE
                if(t.y < high && t.y > 0){
                    t_c = tmenor;
                    hasHit = true;
                }
            }
        }
    }
    //Obtenim les interseccions i mirem quina és la menor.
    float tfront = t_c;
    if(top1->hit(r,t_min, t_max, rec)){
        t_top1 = rec.t;
        hasHit = true;
        if(t_top1 < tfront){tfront = t_top1;}
    }
    if(top2->hit(r,t_min, t_max, rec)){
        t_top2 = rec.t;
        hasHit = true;
        if(t_top2 < tfront){tfront = t_top2;}
    }
    //Si hi hagut una intersecció actualitza la hitInfo amb la més petita.
    if(hasHit){
        rec.t = tfront;
        rec.p = r.pointAtParameter(rec.t);
        rec.normal = (rec.p - center) / radius;
        rec.mat_ptr = material;
    }
    return hasHit;
}

void Cylinder::aplicaTG(TG *t){
    if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}
