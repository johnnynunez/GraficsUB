#include "SceneFactory.h"


void SceneFactory::dataReader (string filename, Scene *s, ObjectFactory::OBJECT_TYPES t) {

    float dim[3][2];
    char *comment_ptr;
    int nwords;
    int numData;
    int numSeries;

    FILE *fp = fopen(filename.c_str(),"r");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        for (int i = 0; i<3; i++) {
            comment_ptr = ReadFile::fetch_line (fp);
            nwords = ReadFile::fetch_words();
            assert(nwords==2);
            for (int j=0; j<2;j++) {
                string word(ReadFile::words[j]);
                dim[i][j] = atof(word.c_str());
            }
        }


        comment_ptr = ReadFile::fetch_line (fp);
        nwords = ReadFile::fetch_words();
        assert(nwords==1);
        string nomTextura(ReadFile::words[0]);

        comment_ptr = ReadFile::fetch_line (fp);
        nwords = ReadFile::fetch_words();
        assert(nwords==1);
        string nS(ReadFile::words[0]);
        numSeries = atoi(nS.c_str());

        comment_ptr = ReadFile::fetch_line (fp);
        nwords = ReadFile::fetch_words();
        assert(nwords==1);
        string nD(ReadFile::words[0]);
        numData = atoi(nD.c_str());

        double vant;
        for (int k=0; k<numSeries; k++) {
            for (int i=0; i<numData; i++) {
                comment_ptr = ReadFile::fetch_line (fp);


                if (comment_ptr == (char *) -1)  /* end-of-file */
                    break;

                /* if we get here, the line was not a comment */
                int nwords = ReadFile::fetch_words();

                assert(nwords==3);
                string sx(ReadFile::words[0]);
                string sy(ReadFile::words[1]);
                string sz(ReadFile::words[2]);
                double x = atof(sx.c_str());
                double y = 0.0;
                double z = atof(sy.c_str());
                double v = atof(sz.c_str());
                // Por cada linea del fichero que no son header

                //Transformem les coordenades llegides cumplint l'escala
                //((Xread - Xminread) / (Xmaxread - Xminread)) = ((Xscene - Xminscene) / (Xmaxscene - Xminscene))

                //obenim Xscene = ((Xread - Xminread)*(Xmaxscene - Xminscene) / (Xmaxread - Xminread)) + Xminscene
                x = (((x - dim[0][0])*(s->DIM_SCENE[0][1] - s->DIM_SCENE[0][0]))/(dim[0][1] - dim[0][0])) + s->DIM_SCENE[0][0];

                //PRUEBA: Formula de las Transparencias
                //Xscene = Xread * ( Xmaxscene - Xminscene) /(xmaxread - xminread) - xminread * ( Xmaxscene - Xminscene) /(xmaxread - xminread) + Xminscene
                //x = x * (dim[0][1] - dim[0][0]) /(s->DIM_SCENE[0][1] - s->DIM_SCENE[0][0]) - s->DIM_SCENE[0][0] * (dim[0][1] - dim[0][0]) /(s->DIM_SCENE[0][1] - s->DIM_SCENE[0][0]) + dim[0][0];

                //la y es constante

                z = (((z - dim[1][0])*(s->DIM_SCENE[1][1] - s->DIM_SCENE[1][0]))/(dim[1][1] - dim[1][0])) + s->DIM_SCENE[1][0];
                //v = (((v - dim[2][0])*(s->DIM_SCENE[2][1] - s->DIM_SCENE[2][0]))/(dim[2][1] - dim[1][0])) + s->DIM_SCENE[2][0];

                //PRUEBA
                //z = z * (dim[2][1] - dim[2][0]) /(s->DIM_SCENE[2][1] - s->DIM_SCENE[2][0]) - s->DIM_SCENE[2][0] * (dim[2][1] - dim[2][0]) /(s->DIM_SCENE[2][1] - s->DIM_SCENE[2][0]) + dim[2][0];


                Object *o;
                if (k!=0) {
                    // Creacio de la animacio que toca
                    Animation *anim = new Animation();
                    anim->frameIni = k;
                    anim->frameFinal = numSeries;
                    anim->transf = new Scale (vec3(2));
                    s->objects[i]->addAnimation(anim);
                }else {
                    o = ObjectFactory::getInstance()->getObject(x, y , z, v, t);
                    o->aplicaTG(new Scale(vec3(v,v,v)));//escalem en funció del valor
                    o->aplicaTG(new Translate(vec3(x,0,z)));//coloquem a la posició l'objecte
                    s->objects.push_back(o);
                }

            }
        }
        fclose(fp);
    }
}

