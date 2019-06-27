#include "Triangle.h"


Triangle::Triangle(vec3 A, vec3 B,vec3 C, float data): Plane(cross(B - A,C - A), A, data)
{
    vertexs = std::vector<vec3>();
    vertexs.push_back(A);
    vertexs.push_back(B);
    vertexs.push_back(C);
    normal = normalize(cross(B - A,C - A));
}

Triangle::Triangle(vec3 cord, float r, float d):Plane(cross(vec3(0,1,0) - vec3(1,0,0),vec3(0,0,1) - vec3(1,0,0)), vec3(1,0,0), d){
    this->A = vec3(1,0,0);
    this->B = vec3(0,1,0);
    this->C = vec3(0,0,1);
    vertexs = std::vector<vec3>();
    vertexs.push_back(A);
    vertexs.push_back(B);
    vertexs.push_back(C);
    normal = normalize(cross(B - A,C - A));
    this->aplicaTG(new Translate(cord));
}
bool Triangle::hit(const Ray &r, float t_min, float t_max, HitInfo &info) const{

    float prod=dot(r.dirVector(),normal);
    // Comprovem si fa un hit en el pla que conté el triangle
    if(Plane::hit(r,t_min,t_max,info)){
        if(fabs(prod)<EPSILON){
            return false;
        }
        // Calculem la d, és a dir la distància desde l'origen de coordenades fins al pla
        float d=-dot(normal,vertexs[0]);
        // Calculem la distància t amb la fòrmula que tenim a
        // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
        float t_dist=-((d+dot(normal,r.initialPoint()))/prod);
        vec3 interseccio=r.pointAtParameter(t_dist);
        // Creem les arestes del triangle
        float v1=dot(cross((vertexs[1]-vertexs[0]),interseccio-vertexs[0]),normal);
        float v2=dot(cross((vertexs[2]-vertexs[1]),interseccio-vertexs[1]),normal);
        float v3=dot(cross((vertexs[0]-vertexs[2]),interseccio-vertexs[2]),normal);

        // Mirem si les arestes tenen el mateix signe,
        // per a saber si la intersecció està dintre del triangle
        if((v1<0 && v2<0 && v3<0) || (v1>0 && v2>0 && v3>0)){
            // Si la distància t calculada està dins del rang del raig,
            // actualitzem la info
            if(t_min<t_dist && t_dist<t_max){
                info.t = t_dist;
                info.p = interseccio;
                if(prod<0)
                    info.normal = normal;
                else
                    info.normal = -normal;
                info.mat_ptr = material;
                return true;
            }
            return false;
        }else{
            return false;
        }
    }
    return false;
}

void Triangle::aplicaTG(TG *t){
    vec4 v1(vertexs[0], 1.0);
    vec4 v2(vertexs[1], 1.0);
    vec4 v3(vertexs[2], 1.0);

    if (dynamic_cast<Translate *>(t)) {//desplacem vertexs

        v1 = t->getTG() * v1;
        v2 = t->getTG() * v2;
        v3 = t->getTG() * v3;

        vertexs[0].x = vertexs[0].x; vertexs[0].y = v1.y; vertexs[0].z = v1.z;
        vertexs[1].x = vertexs[1].x; vertexs[1].y = vertexs[1].y; vertexs[1].z = v2.z;
        vertexs[2].x = vertexs[2].x; vertexs[2].y = v3.y; vertexs[2].z = v3.z;

    }
    if(dynamic_cast<Scale *>(t)){//escalem els vertexs
        v1 = t->getTG() * v1;
        v2 = t->getTG() * v2;
        v3 = t->getTG() * v3;

        float factorA = vertexs[0].x/v1.x;
        float factorB = vertexs[1].x / v2.x;
        float factorC = vertexs[2].x / v3.x;

        vertexs[0].x * factorA; vertexs[0].y * factorA; vertexs[0].z * factorA;
        vertexs[1].x * factorB; vertexs[1].y * factorB; vertexs[1].z * factorB;
        vertexs[2].x * factorC; vertexs[2].y * factorC; vertexs[2].z * factorC;
    }

}
