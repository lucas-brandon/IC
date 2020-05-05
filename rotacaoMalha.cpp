#include <cmath>
#include <vector>

using namespace std;
using glm::vec3;

GLint rotx=0;
GLint roty=1;
GLint rotz=0;
GLint posx=0;
GLint posy=0;
GLint posz=20;
GLint lookx=0;
GLint looky=0;
GLint lookz=0;

//matriz de translacao generica (mtg)
GLfloat mtg[4][4] = {
      {1,0,0,0},
      {0,1,0,0},
      {0,0,1,0},
      {0,0,0,1},
      };

//matriz de rotacao e translacao eixo x
//matriz de translação volta
GLfloat mtv[4][4] = {
      {1,0,0,0},
      {0,1,0,0},
      {0,0,1,0},
      {0,0,0,1},
      };

//matriz de rotacao e translacao eixo x
//matriz de translação ida ao centro
GLfloat mtc[4][4] = {
      {1,0,0,0},
      {0,1,0,0},
      {0,0,1,0},
      {0,0,0,1},
      };

//matriz de rotacao genérica em torno do eixo x
// acessar indices mrx{1}{1},mrx{1}{2}, mrx{2}{1},mrx{2}{2}
GLfloat mrx[4][4] = {
      {1,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,1},
      };

//matriz de rotacao genérica em torno do eixo y
//
GLfloat mry[4][4] = {
      {0,0,0,0},
      {0,1,0,0},
      {0,0,0,0},
      {0,0,0,1},
      };

//matriz de rotacao genérica em torno do eixo z
GLfloat mrz[4][4] = {
      {1,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,1},
      };




void multiplicaMatriz(GLfloat aux[][4],GLfloat m1[][4], GLfloat m2[][4]){

  for(int i=0;i<4;i++){

      for(int j=0;j<4;j++){

          aux[i][j]=0;
          for(int k=0;k<4;k++){

                aux[i][j] += m1[i][k] * m2[k][j];

          }


      }


    }


}
void printMatriz(GLfloat m[][4]){

  for(int i=0;i<4;i++){

      for(int j=0;j<4;j++){

          cout<<m[i][j]<<" ";

      }

      cout<<endl;
  }

cout<<endl;

}

void transladarEixoCubo(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ){

  mtg[0][3] = deltaX;
  mtg[1][3] = deltaY;
  mtg[2][3] = deltaZ;
  GLfloat vet[3];


for(int i=0;i<pontoCubo.size();i++){

    for(int j=0;j<3;j++){

       vet[j]=mtg[j][0]*pontoCubo[i].x + mtg[j][1]*pontoCubo[i].y + mtg[j][2]*pontoCubo[i].z + mtg[j][3];

    }

    pontoCubo[i].x=vet[0];
    pontoCubo[i].y=vet[1];
    pontoCubo[i].z=vet[2];

  }

}

void escalarCuboY(GLfloat eY){

  mtg[0][3] = 0;
  mtg[1][3] = 0;
  mtg[2][3] = 0;
  GLfloat vet[3];


for(int i=0;i<pontoCubo.size();i++){

    for(int j=0;j<3;j++){

       vet[j]=eY*(mtg[j][0]*pontoCubo[i].x + mtg[j][1]*pontoCubo[i].y + mtg[j][2]*pontoCubo[i].z + mtg[j][3]);

    }

    pontoCubo[i].x=vet[0];
    pontoCubo[i].y=vet[1];
    pontoCubo[i].z=vet[2];

  }

}




void transladarObjeto(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ){

  mtg[0][3] = deltaX;
  mtg[1][3] = deltaY;
  mtg[2][3] = deltaZ;
  GLfloat vet[3];


for(int i=1;i<vertices.size();i++){

    for(int j=0;j<3;j++){

       vet[j]=mtg[j][0]*vertices[i].x + mtg[j][1]*vertices[i].y + mtg[j][2]*vertices[i].z + mtg[j][3];

    }

    vertices[i].x=vet[0];
    vertices[i].y=vet[1];
    vertices[i].z=vet[2];

  }

}


void transladarEixoEsfera(GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ){

  mtg[0][3] = deltaX;
  mtg[1][3] = deltaY;
  mtg[2][3] = deltaZ;
  GLfloat vet[3];


for(int i=0;i<pontoEsfera.size();i++){

   for(int k=0;k<pontoEsfera[i].size();k++){

    for(int j=0;j<3;j++){

       vet[j]=mtg[j][0]*pontoEsfera[i][k].x + mtg[j][1]*pontoEsfera[i][k].y + mtg[j][2]*pontoEsfera[i][k].z + mtg[j][3];

    }

    pontoEsfera[i][k].x=vet[0];
    pontoEsfera[i][k].y=vet[1];
    pontoEsfera[i][k].z=vet[2];

  }

  }

}


void rotacionarMalha3DX(GLfloat angulo){



     angulo = angulo * M_PI/180;

     GLfloat centerx = (minx+maxx)/2;
     GLfloat centery = (miny+maxy)/2;
     GLfloat centerz = (minz+maxz)/2;




     for(int i=0;i<vertices.size();i++){

        //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

        //setando os valores da matriz de translação ao centro
	      mtc[0][3] = -centerx;
        mtc[1][3] = -centery;
        mtc[2][3] = -centerz;


        //setando os valores da matriz de volta
        mtv[0][3] = centerx;
        mtv[1][3] = centery;
        mtv[2][3] = centerz;

        //setando os valores da matriz de rotação
        mrx[1][1] = cos(angulo);
        mrx[2][1] = sin(angulo);
        mrx[1][2] = -mrx[2][1];
        mrx[2][2] = cos(angulo);


        GLfloat aux1[4][4],aux2[4][4];

        multiplicaMatriz(aux1,mtv,mrx);
        multiplicaMatriz(aux2,aux1,mtc);
        GLfloat vet[3];



        for(int j=0;j<3;j++){

           vet[j]=aux2[j][0]*vertices[i].x + aux2[j][1]*vertices[i].y + aux2[j][2]*vertices[i].z + aux2[j][3];

        }

        vertices[i].x=vet[0];
        vertices[i].y=vet[1];
        vertices[i].z=vet[2];

        //cout<<"xf: "<<vertices[i].x<<" yf: "<<vertices[i].y<<" zf: "<<vertices[i].z<<endl;
        //getchar();
     }



}

void rotacionarMalha3DY(GLfloat angulo){



     angulo = angulo * M_PI/180;

     GLfloat centerx = (minx+maxx)/2;
     GLfloat centery = (miny+maxy)/2;
     GLfloat centerz = (minz+maxz)/2;



     for(int i=0;i<vertices.size();i++){

        //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

        //setando os valores da matriz de translação ao centro
	      mtc[0][3] = -centerx;
        mtc[1][3] = -centery;
        mtc[2][3] = -centerz;


        //setando os valores da matriz de volta
        mtv[0][3] = centerx;
        mtv[1][3] = centery;
        mtv[2][3] = centerz;

        //setando os valores da matriz de rotação
        mry[0][0] = cos(angulo);
        mry[0][2] = sin(angulo);
        mry[2][0] = -mry[0][2];
        mry[2][2] = cos(angulo);


        GLfloat aux1[4][4],aux2[4][4];

        multiplicaMatriz(aux1,mtv,mry);
        multiplicaMatriz(aux2,aux1,mtc);
        GLfloat vet[3];

        for(int j=0;j<3;j++){

           vet[j]=aux2[j][0]*vertices[i].x + aux2[j][1]*vertices[i].y + aux2[j][2]*vertices[i].z + aux2[j][3];

        }

        vertices[i].x=vet[0];
        vertices[i].y=vet[1];
        vertices[i].z=vet[2];

     }

}

void rotacionarMalha3DXCubo(GLfloat angulo){
    contRotationX += angulo;

    while(contRotationX >= 360){
      contRotationX-=360;
    }

     angulo = angulo * M_PI/180;

     GLfloat maxxc=-100;
     GLfloat maxyc=-100;
     GLfloat maxzc=-100;
     GLfloat minxc=100;
     GLfloat minyc=100;
     GLfloat minzc=100;

     for(int i=0;i<pontoCubo.size();i++){

       if(maxxc < pontoCubo[i].x){

            maxxc = pontoCubo[i].x;

       }if(maxyc < pontoCubo[i].y){

            maxyc = pontoCubo[i].y;

       }if(maxzc < pontoCubo[i].z){

            maxzc = pontoCubo[i].z;

       }if(minxc > pontoCubo[i].x){

            minxc = pontoCubo[i].x;

       }if(minyc > pontoCubo[i].y){

            minyc = pontoCubo[i].y;

       }if(minzc > pontoCubo[i].z){

            minzc = pontoCubo[i].z;

       }


     }

     GLfloat centerx = (minxc+maxxc)/2;
     GLfloat centery = (minyc+maxyc)/2;
     GLfloat centerz = (minzc+maxzc)/2;


     for(int i=0;i<pontoCubo.size();i++){

        //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

        //setando os valores da matriz de translação ao centro
	      mtc[0][3] = -centerx;
        mtc[1][3] = -centery;
        mtc[2][3] = -centerz;


        //setando os valores da matriz de volta
        mtv[0][3] = centerx;
        mtv[1][3] = centery;
        mtv[2][3] = centerz;

        //setando os valores da matriz de rotação
        mrx[1][1] = cos(angulo);
        mrx[2][1] = sin(angulo);
        mrx[1][2] = -mrx[2][1];
        mrx[2][2] = cos(angulo);


        GLfloat aux1[4][4],aux2[4][4];

        multiplicaMatriz(aux1,mtv,mrx);
        multiplicaMatriz(aux2,aux1,mtc);
        GLfloat vet[3];

        for(int j=0;j<3;j++){

           vet[j]=aux2[j][0]*pontoCubo[i].x + aux2[j][1]*pontoCubo[i].y + aux2[j][2]*pontoCubo[i].z + aux2[j][3];

        }

        pontoCubo[i].x=vet[0];
        pontoCubo[i].y=vet[1];
        pontoCubo[i].z=vet[2];

        //cout<<"xf: "<<vertices[i].x<<" yf: "<<vertices[i].y<<" zf: "<<vertices[i].z<<endl;
        //getchar();
     }



}

void rotacionarMalha3DYCubo(GLfloat angulo){

    contRotationY += angulo;

    while(contRotationY >= 360){
      contRotationY-=360;
    }

     angulo = angulo * M_PI/180;

     GLfloat maxxc=-100;
     GLfloat maxyc=-100;
     GLfloat maxzc=-100;
     GLfloat minxc=100;
     GLfloat minyc=100;
     GLfloat minzc=100;

     for(int i=0;i<pontoCubo.size();i++){

       if(maxxc < pontoCubo[i].x){

            maxxc = pontoCubo[i].x;

       }if(maxyc < pontoCubo[i].y){

            maxyc = pontoCubo[i].y;

       }if(maxzc < pontoCubo[i].z){

            maxzc = pontoCubo[i].z;

       }if(minxc > pontoCubo[i].x){

            minxc = pontoCubo[i].x;

       }if(minyc > pontoCubo[i].y){

            minyc = pontoCubo[i].y;

       }if(minzc > pontoCubo[i].z){

            minzc = pontoCubo[i].z;

       }


     }


     GLfloat centerx = (minxc+maxxc)/2;
     GLfloat centery = (minyc+maxyc)/2;
     GLfloat centerz = (minzc+maxzc)/2;


     for(int i=0;i<pontoCubo.size();i++){

        //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

        //setando os valores da matriz de translação ao centro
	      mtc[0][3] = -centerx;
        mtc[1][3] = -centery;
        mtc[2][3] = -centerz;


        //setando os valores da matriz de volta
        mtv[0][3] = centerx;
        mtv[1][3] = centery;
        mtv[2][3] = centerz;

        //setando os valores da matriz de rotação
        mry[0][0] = cos(angulo);
        mry[0][2] = sin(angulo);
        mry[2][0] = -mry[0][2];
        mry[2][2] = cos(angulo);


        GLfloat aux1[4][4],aux2[4][4];

        multiplicaMatriz(aux1,mtv,mry);
        multiplicaMatriz(aux2,aux1,mtc);
        GLfloat vet[3];

        for(int j=0;j<3;j++){

           vet[j]=aux2[j][0]*pontoCubo[i].x + aux2[j][1]*pontoCubo[i].y + aux2[j][2]*pontoCubo[i].z + aux2[j][3];

        }

        pontoCubo[i].x=vet[0];
        pontoCubo[i].y=vet[1];
        pontoCubo[i].z=vet[2];

     }

}



void rotacionarMalha3DYEsfera(GLfloat angulo){

     angulo = angulo * M_PI/180;

     GLfloat maxxe=-100;
     GLfloat maxye=-100;
     GLfloat maxze=-100;
     GLfloat minxe=100;
     GLfloat minye=100;
     GLfloat minze=100;

  for(int i=0;i<pontoEsfera.size();i++){


     for(int k=0;k<pontoEsfera[i].size();k++){

       if(maxxe < pontoEsfera[i][k].x){

            maxxe = pontoEsfera[i][k].x;

       }if(maxye < pontoEsfera[i][k].y){

            maxye = pontoEsfera[i][k].y;

       }if(maxze < pontoEsfera[i][k].z){

            maxze = pontoEsfera[i][k].z;

       }if(minxe > pontoEsfera[i][k].x){

            minxe = pontoEsfera[i][k].x;

       }if(minye > pontoEsfera[i][k].y){

            minye = pontoEsfera[i][k].y;

       }if(minze > pontoEsfera[i][k].z){

            minze = pontoEsfera[i][k].z;

       }


     }
}
     GLfloat centerx = (minxe+maxxe)/2;
     GLfloat centery = (minye+maxye)/2;
     GLfloat centerz = (minze+maxze)/2;


     for(int i=0;i<pontoEsfera.size();i++){


        for(int k=0;k<pontoEsfera[i].size();k++){

        //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

        //setando os valores da matriz de translação ao centro
	      mtc[0][3] = -centerx;
        mtc[1][3] = -centery;
        mtc[2][3] = -centerz;


        //setando os valores da matriz de volta
        mtv[0][3] = centerx;
        mtv[1][3] = centery;
        mtv[2][3] = centerz;

        //setando os valores da matriz de rotação
        mry[0][0] = cos(angulo);
        mry[0][2] = sin(angulo);
        mry[2][0] = -mry[0][2];
        mry[2][2] = cos(angulo);


        GLfloat aux1[4][4],aux2[4][4];

        multiplicaMatriz(aux1,mtv,mry);
        multiplicaMatriz(aux2,aux1,mtc);
        GLfloat vet[3];

        for(int j=0;j<3;j++){

           vet[j]=aux2[j][0]*pontoEsfera[i][k].x + aux2[j][1]*pontoEsfera[i][k].y + aux2[j][2]*pontoEsfera[i][k].z + aux2[j][3];

        }

        pontoEsfera[i][k].x=vet[0];
        pontoEsfera[i][k].y=vet[1];
        pontoEsfera[i][k].z=vet[2];

     }
   }

}

void rotacionarMalha3DXEsfera(GLfloat angulo){

  GLfloat maxxe=-100;
  GLfloat maxye=-100;
  GLfloat maxze=-100;
  GLfloat minxe=100;
  GLfloat minye=100;
  GLfloat minze=100;

for(int i=0;i<pontoEsfera.size();i++){


  for(int j=0;j<pontoEsfera[i].size();i++){

    if(maxxe < pontoEsfera[i][j].x){

         maxxe = pontoEsfera[i][j].x;

    }if(maxye < pontoEsfera[i][j].y){

         maxye = pontoEsfera[i][j].y;

    }if(maxze < pontoEsfera[i][j].z){

         maxze = pontoEsfera[i][j].z;

    }if(minxe > pontoEsfera[i][j].x){

         minxe = pontoEsfera[i][j].x;

    }if(minye > pontoEsfera[i][j].y){

         minye = pontoEsfera[i][j].y;

    }if(minze > pontoEsfera[i][j].z){

         minze = pontoEsfera[i][j].z;

    }


  }
}
  GLfloat centerx = (minxe+maxxe)/2;
  GLfloat centery = (minye+maxye)/2;
  GLfloat centerz = (minze+maxze)/2;



  for(int i=0;i<pontoEsfera.size();i++){


     for(int k=0;k<pontoEsfera[i].size();k++){

        //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

        //setando os valores da matriz de translação ao centro
	      mtc[0][3] = -centerx;
        mtc[1][3] = -centery;
        mtc[2][3] = -centerz;


        //setando os valores da matriz de volta
        mtv[0][3] = centerx;
        mtv[1][3] = centery;
        mtv[2][3] = centerz;

        //setando os valores da matriz de rotação
        mrx[1][1] = cos(angulo);
        mrx[2][1] = sin(angulo);
        mrx[1][2] = -mrx[2][1];
        mrx[2][2] = cos(angulo);


        GLfloat aux1[4][4],aux2[4][4];

        multiplicaMatriz(aux1,mtv,mrx);
        multiplicaMatriz(aux2,aux1,mtc);
        GLfloat vet[3];



        for(int j=0;j<3;j++){

           vet[j]=aux2[j][0]*pontoEsfera[i][k].x + aux2[j][1]*pontoEsfera[i][k].y + aux2[j][2]*pontoEsfera[i][k].z + aux2[j][3];

        }

        pontoEsfera[i][k].x=vet[0];
        pontoEsfera[i][k].y=vet[1];
        pontoEsfera[i][k].z=vet[2];

        //cout<<"xf: "<<vertices[i].x<<" yf: "<<vertices[i].y<<" zf: "<<vertices[i].z<<endl;
        //getchar();
     }
}


}

void rotacionarCameraEixoX(GLfloat angulo){


       angulo = angulo * M_PI/180;



       GLfloat centerx = posx;
       GLfloat centery = posy;
       GLfloat centerz = posz;

          //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

          //setando os valores da matriz de translação ao centro
         mtc[0][3] = -centerx;
          mtc[1][3] = -centery;
          mtc[2][3] = -centerz;


          //setando os valores da matriz de volta
          mtv[0][3] = centerx;
          mtv[1][3] = centery;
          mtv[2][3] = centerz;

          //setando os valores da matriz de rotação
          mrx[1][1] = cos(angulo);
          mrx[2][1] = sin(angulo);
          mrx[1][2] = -mrx[2][1];
          mrx[2][2] = cos(angulo);


          GLfloat aux1[4][4],aux2[4][4];

          multiplicaMatriz(aux1,mtv,mrx);
          multiplicaMatriz(aux2,aux1,mtc);
          GLfloat vet[3];

          for(int j=0;j<3;j++){

             vet[j]=aux2[j][0]*lookx + aux2[j][1]*looky + aux2[j][2]*lookz + aux2[j][3];

          }

          lookx=vet[0];
          looky=vet[1];
          lookz=vet[2];

        //  vec3 vv = vec3(vet[0],vet[1],vet[2]);

          //return vv;

          cout<<"Eixo X: "<<lookx<<" "<<looky<<" "<<lookz<<endl;

}
vec3 rotacionarCameraEixoY(GLfloat angulo){


       angulo = angulo * M_PI/180;

       GLfloat centerx = posx;
       GLfloat centery = posy;
       GLfloat centerz = posz;

          //cout<<"x: "<<vertices[i].x<<" y: "<<vertices[i].y<<" z: "<<vertices[i].z<<endl;

          //setando os valores da matriz de translação ao centro
          mtc[0][3] = -centerx;
          mtc[1][3] = -centery;
          mtc[2][3] = -centerz;


          //setando os valores da matriz de volta
          mtv[0][3] = centerx;
          mtv[1][3] = centery;
          mtv[2][3] = centerz;

          //setando os valores da matriz de rotação
          mry[0][0] = cos(angulo);
          mry[0][2] = sin(angulo);
          mry[2][0] = -mry[0][2];
          mry[2][2] = cos(angulo);


          GLfloat aux1[4][4],aux2[4][4];

          multiplicaMatriz(aux1,mtv,mry);
          multiplicaMatriz(aux2,aux1,mtc);
          GLfloat vet[3];

          for(int j=0;j<3;j++){

             vet[j]=aux2[j][0]*lookx + aux2[j][1]*looky + aux2[j][2]*lookz + aux2[j][3];

          }

          lookx=vet[0];
          looky=vet[1];
          lookz=vet[2];

          //vec3 vv = vec3(vet[0],vet[1],vet[2]);

          //return vv;
          cout<<"Eixo Y: "<<lookx<<" "<<looky<<" "<<lookz<<endl;

}
