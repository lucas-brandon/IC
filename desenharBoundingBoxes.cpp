#include <iostream>
#include "transformacaoBoundingBoxes.cpp"
#include <cmath>
using namespace std;

float x, y, z, xy;
float radius = 2.0f;
int sectorCount=10,stackCount=10;
float sectorStep = 2 * M_PI / sectorCount;
float stackStep = M_PI / stackCount;
float sectorAngle, stackAngle;

void inicializaPontosCubo(){

  //pontoCubo[0].x=0;pontoCubo[0].y=0;pontoCubo[0].z=-0.40;           //b4
  //pontoCubo[1].x=0;pontoCubo[1].y=0.40f;pontoCubo[1].z=-0.40f;      //t4
  //pontoCubo[2].x=0;pontoCubo[2].y=0.40f;pontoCubo[2].z=-1.20f;      //t1
  //pontoCubo[3].x=0;pontoCubo[3].y=0;pontoCubo[3].z=-1.20f;          //b1
  //pontoCubo[4].x=0.60f;pontoCubo[4].y=0;pontoCubo[4].z=-1.20f;      //b2
  //pontoCubo[5].x=0.60f;pontoCubo[5].y=0.40f;pontoCubo[5].z=-1.20f;  //t2
  //pontoCubo[6].x=0.60f;pontoCubo[6].y=0.40f;pontoCubo[6].z=-0.40;   //t3
  //pontoCubo[7].x=0.60f;pontoCubo[7].y=0;pontoCubo[7].z=-0.40;       //b3

  pontoCubo[0].x=0;pontoCubo[0].y=0;pontoCubo[0].z=-0.80;           //b4
  pontoCubo[1].x=0;pontoCubo[1].y=1.20f;pontoCubo[1].z=-0.80f;      //t4
  pontoCubo[2].x=0;pontoCubo[2].y=1.20f;pontoCubo[2].z=-2.40f;      //t1
  pontoCubo[3].x=0;pontoCubo[3].y=0;pontoCubo[3].z=-2.40f;          //b1
  pontoCubo[4].x=1.20f;pontoCubo[4].y=0;pontoCubo[4].z=-2.40f;      //b2
  pontoCubo[5].x=1.20f;pontoCubo[5].y=1.20f;pontoCubo[5].z=-2.40f;  //t2
  pontoCubo[6].x=1.20f;pontoCubo[6].y=1.20f;pontoCubo[6].z=-0.80;   //t3
  pontoCubo[7].x=1.20f;pontoCubo[7].y=0;pontoCubo[7].z=-0.80;       //b3

  /*
 for(int i=0;i<pontoCubo.size();i++){

    pontoCubo[i].x=pontoCubo[i].x/5;
    pontoCubo[i].y=pontoCubo[i].y/5;
    pontoCubo[i].z=pontoCubo[i].z/5;

 }*/


}
void inicializaPontosEsfera(){



 for(int i=0;i<=stackCount;i++){
      vector<vec3> auxvet;
      pontoEsfera.push_back(auxvet);
 }

  for(int i = 0; i <= stackCount; ++i)
  {
      stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
      xy = radius * cosf(stackAngle);             // r * cos(u)
      z = radius * sinf(stackAngle);              // r * sin(u)

      // add (sectorCount+1) vertices per stack
      // the first and last vertices have same position and normal, but different tex coords
      for(int j = 0; j <= sectorCount; ++j)
      {
          sectorAngle = j * sectorStep;           // starting from 0 to 2pi

          // vertex position (x, y, z)
          x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
          y = xy * sinf(sectorAngle);

          vec3 v = vec3(x,y,z);
          pontoEsfera[i].push_back(v);

      }
  }


}

void desenharCubo(){
    CUBO = true;

     glBegin(GL_LINES);

       //lado 1
       //Aresta 1
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(pontoCubo[0].x,pontoCubo[0].y,pontoCubo[0].z);

       glVertex3f(pontoCubo[1].x,pontoCubo[1].y,pontoCubo[1].z);

       //Aresta 2

       glVertex3f(pontoCubo[1].x,pontoCubo[1].y,pontoCubo[1].z);

       glVertex3f(pontoCubo[2].x,pontoCubo[2].y,pontoCubo[2].z);

       //Aresta 3

       glVertex3f(pontoCubo[2].x,pontoCubo[2].y,pontoCubo[2].z);

       glVertex3f(pontoCubo[3].x,pontoCubo[3].y,pontoCubo[3].z);

       //Aresta 4

       glVertex3f(pontoCubo[3].x,pontoCubo[3].y,pontoCubo[3].z);

       glVertex3f(pontoCubo[0].x,pontoCubo[0].y,pontoCubo[0].z);


       //lado 2
       //Aresta 1

       glVertex3f(pontoCubo[0].x,pontoCubo[0].y,pontoCubo[0].z);

       glVertex3f(pontoCubo[7].x,pontoCubo[7].y,pontoCubo[7].z);

       //Aresta 2

       glVertex3f(pontoCubo[7].x,pontoCubo[7].y,pontoCubo[7].z);

       glVertex3f(pontoCubo[6].x,pontoCubo[6].y,pontoCubo[6].z);

       //Aresta 3

       glVertex3f(pontoCubo[6].x,pontoCubo[6].y,pontoCubo[6].z);

       glVertex3f(pontoCubo[1].x,pontoCubo[1].y,pontoCubo[1].z);

       //Aresta 4

       glVertex3f(pontoCubo[1].x,pontoCubo[1].y,pontoCubo[1].z);

       glVertex3f(pontoCubo[0].x,pontoCubo[0].y,pontoCubo[0].z);


       //lado 3
       //Aresta 1

       glVertex3f(pontoCubo[6].x,pontoCubo[6].y,pontoCubo[6].z);

       glVertex3f(pontoCubo[5].x,pontoCubo[5].y,pontoCubo[5].z);

       //Aresta 2

       glVertex3f(pontoCubo[5].x,pontoCubo[5].y,pontoCubo[5].z);

       glVertex3f(pontoCubo[4].x,pontoCubo[4].y,pontoCubo[4].z);

       //Aresta 3

       glVertex3f(pontoCubo[4].x,pontoCubo[4].y,pontoCubo[4].z);

       glVertex3f(pontoCubo[7].x,pontoCubo[7].y,pontoCubo[7].z);


       //lado 4
       //Aresta 1

       glVertex3f(pontoCubo[2].x,pontoCubo[2].y,pontoCubo[2].z);

       glVertex3f(pontoCubo[5].x,pontoCubo[5].y,pontoCubo[5].z);

       //Aresta 2

       glVertex3f(pontoCubo[3].x,pontoCubo[3].y,pontoCubo[3].z);

       glVertex3f(pontoCubo[4].x,pontoCubo[4].y,pontoCubo[4].z);


     glEnd();


}
void desenharEsfera(){


for(int i=0;i<pontoEsfera.size();i++){

    glBegin(GL_LINE_STRIP);

    for(int j=0;j<pontoEsfera[i].size();j++){

        glColor3f(1.0f,0.0,0.0);
        glVertex3f(pontoEsfera[i][j].x,pontoEsfera[i][j].y,pontoEsfera[i][j].z);

    }

    glEnd();

}

for(int i=0;i<=sectorCount;++i){

        glBegin(GL_LINE_STRIP);

     for(int j=0;j<=stackCount;++j){
          glColor3f(1.0f,0.0,0.0);
          glVertex3f(pontoEsfera[j][i].x,pontoEsfera[j][i].y,pontoEsfera[j][i].z);

     }

     glEnd();
}


}
void desenharPiramide(){



}
