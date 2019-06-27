#include "BoundaryObject.h"

BoundaryObject::BoundaryObject(string s, float data) : Object(data)
{

    readObj(s);//llegim objecte
    vec3 minX, maxX;
    vec3 minY, maxY;
    vec3 minZ, maxZ;
    //dimensions per la capça contenidora del objecte
  for (Cara c : cares) {//llegim totes les cares i creem els triangles del mesh
      int id0 = c.idxVertices[0];
      int id1 = c.idxVertices[1];
      int id2 = c.idxVertices[2];
      //vertexs que formen la cara(triangle)
      minX = min(vec3(vertexs[id0]),minX);
      maxX = max(vec3(vertexs[id0]),maxX);
      minY = min(vec3(vertexs[id1]),minY);
      maxY = max(vec3(vertexs[id1]),maxY);
      minZ = min(vec3(vertexs[id2]),minZ);
      maxZ = max(vec3(vertexs[id2]),maxZ);
      //obtenim maxims i minims
      Triangle *triangle = new Triangle(vec3(vertexs[id0]),vec3(vertexs[id1]),vec3(vertexs[id2]),data);
      triangles.push_back(triangle);
      //afegim la cara
  }

  bounds = new Cube(minX, maxX, data);//capça contenidora

  //this->centre = vec3(((maxX+minX)/2),((maxY+minY)/2),((maxZ+minZ)/2));
}

BoundaryObject::~BoundaryObject() {

    for (Triangle* t: triangles) {
        delete t;
    }
    delete bounds;
    triangles.clear();
    vertexs.clear();
    cares.clear();
    //eliminem tots els triangles,cares,vertexs i capça contenidora
}

bool BoundaryObject::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    float t_menor(std::numeric_limits<float>::infinity());
    bool h = false;
    if(bounds->hit(r,t_min,t_max,info)){
        for (Triangle* t : triangles) {//provem tots els hits i ens quedem el triangle de t mes petita ja que sera la primera en xocar
            if(t->hit(r,t_min,t_max,info)) {
                if(info.t < t_menor) {
                    t_menor = info.t;
                }
                h = true;
            }
        }
    }
    
    // actualitzem info
    info.t = t_menor;
    info.p = r.pointAtParameter(info.t);
    info.normal = vec3(info.p.x,0,info.p.z);
    info.mat_ptr = material;
    
    return h;
}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void BoundaryObject::readObj(string filename){

    FILE *fp = fopen(filename.c_str(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                string sx(ReadFile::words[1]);
                string sy(ReadFile::words[2]);
                string sz(ReadFile::words[3]);
                double x = atof(sx.c_str());
                double y = atof(sy.c_str());
                double z = atof(sz.c_str());

                if (nwords == 5) {
                    string sw(ReadFile::words[4]);
                    double w = atof(sw.c_str());
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(vec4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadFile::words[1], nwords-1, this, 0);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    fclose(fp);
}

/**
 * @brief BoundaryObject::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */
void BoundaryObject::construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}

void BoundaryObject::aplicaTG(TG *t){
    if (dynamic_cast<Translate *>(t)) {//movem tots els triangles
        bounds->aplicaTG(t);
    }
    if (dynamic_cast<Scale *>(t)){//escalem tots els triangles
        for (Triangle* tr: triangles) {
            tr->aplicaTG(t);
        }
    }
}
