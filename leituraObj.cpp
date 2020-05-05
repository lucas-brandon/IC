#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtx/io.hpp"
#include "desenharBoundingBoxes.cpp"
#include <cmath>
#include <fstream>



struct Face{

   int iv1;
   int iv2;
   int iv3;
   int in1;
   int in2;
   int in3;


};
vector <Face> faces;
vector <Face> fSeparadoStruct;
vector <int>  fSeparadoBool;
int contSeparado=0;
void desenharSala();
using namespace std;
using glm::vec3;


GLfloat maxx=-100;
GLfloat maxy=-100;
GLfloat maxz=-100;
GLfloat minx=100;
GLfloat miny=100;
GLfloat minz=100;

void zerarBool(){


   for(int i=0;i<faces.size();i++){

        fSeparadoBool.push_back(0);

  }

}

bool loadObjFromArchive(char * path, char tipo){

	vector<vec3> temp_vertices;
	vector<vec3> temp_faces;
	vector<vec3> temp_normals;
	vector<vec3> temp_rgb;

	FILE * file = fopen(path, "r");
        FILE * fileCount = fopen(path, "r");

        if( file == NULL){

             printf("Not possible to read the file, please verify if it's an obj type");
             return false;

	}



  if(tipo == 'h'){//hololens

     int contVerticeInt=0;
     int ponteiroArquivo;

     while(1){

       char contVerticeChar[500];
       ponteiroArquivo = fscanf(fileCount,"%s",contVerticeChar);

       if(ponteiroArquivo == EOF){

         break;

       }

       if(contVerticeChar[0] == 'v' && contVerticeChar[1] != 'n'){

         contVerticeInt++;

       }

     }

     cout<<"Total de vertices: "<<contVerticeInt<<endl;
     grafo.preencherGrafo(contVerticeInt);

     int cont = 0;
     while(1){

       char lineHeader[500];
       int res = fscanf (file,"%s",lineHeader);

          if (res == EOF){
              break;
          }
		      ind.push_back(cont);
		      cont++;
          if(lineHeader[0] == 'v' && lineHeader[1] == 'n'){

              vec3 vert;
              fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
		          normals.push_back(vert);

           }

           else if(lineHeader[0] == 'v' && lineHeader[1] != 'i'){
               vec3 vert;
               vec3 color;
               fscanf(file, "%f %f %f \n", &vert.x, &vert.y, &vert.z);

               if(minx > vert.x){

                    minx=vert.x;

                }
                if(miny > vert.y){

                    miny=vert.y;

                }
                if(minz > vert.z){

                    minz=vert.z;

                }
                if(maxx < vert.x){

                    maxx=vert.x;

                }
                if(maxy < vert.y){

                    maxy=vert.y;

                }
                if(maxz < vert.z){

                    maxz=vert.z;

                }

                color.x = 0.4f;
                color.y = 0.4f;
                color.z = 0.4f;



		            vertices.push_back(vert);
                rgb.push_back(color);
                texture2d.push_back(false);
                texture3d.push_back(false);
                textureIndices.push_back(vert);


                 }else if(lineHeader[0] == 'f'){

                     int v1=0,n1=0,v2=0,n2=0,v3=0,n3=0;
                     fscanf(file, "%d//%d %d//%d %d//%d\n", &v1, &n1, &v2, &n2, &v3,&n3);
                     Face f;
                     f.iv1 = v1;
                     f.iv2 = v2;
                     f.iv3 = v3;
                     f.in1 = n1;
                     f.in2 = n2;
                     f.in3 = n3;
                     faces.push_back(f);
                     grafo.lista[f.iv1].push_back(f.iv2);
                     grafo.lista[f.iv1].push_back(f.iv3);
                     grafo.lista[f.iv2].push_back(f.iv1);
                     grafo.lista[f.iv3].push_back(f.iv1);
                     grafo.lista[f.iv2].push_back(f.iv3);
                     grafo.lista[f.iv3].push_back(f.iv2);

		 }

             }








        }
  else if(tipo == 'b'){//bundlefusion

       int contVerticeInt=0;
       int ponteiroArquivo;

       while(1){

         char contVerticeChar[500];
         ponteiroArquivo = fscanf(fileCount,"%s",contVerticeChar);

        if(ponteiroArquivo == EOF){

            break;

        }

        if(contVerticeChar[0] == 'v' && contVerticeChar[1] != 'n'){

            contVerticeInt++;

          }

      }

      cout<<"Total de vertices: "<<contVerticeInt<<endl;
      grafo.preencherGrafo(contVerticeInt);

	     int cont = 0;
       while(1){

          char lineHeader[500];
          int res = fscanf (file,"%s",lineHeader);

          if (res == EOF){
              break;
          }
		      ind.push_back(cont);
		      cont++;
          if(lineHeader[0] == 'v' && lineHeader[1] == 'n'){

              vec3 vert;
              fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
		          normals.push_back(vert);

           }

           else if(lineHeader[0] == 'v' && lineHeader[1] != 'i'){
               vec3 vert;
               vec3 color;
               fscanf(file, "%f %f %f %f %f %f\n", &vert.x, &vert.y, &vert.z, &color.x,&color.y,&color.z);

               if(minx > vert.x){

                    minx=vert.x;

                }
                if(miny > vert.y){

                    miny=vert.y;

                }
                if(minz > vert.z){

                    minz=vert.z;

                }
                if(maxx < vert.x){

                    maxx=vert.x;

                }
                if(maxy < vert.y){

                    maxy=vert.y;

                }
                if(maxz < vert.z){

                    maxz=vert.z;

                }

		            vertices.push_back(vert);
                rgb.push_back(color);
                texture2d.push_back(false);
                texture3d.push_back(false);
                textureIndices.push_back(vert);


                 }else if(lineHeader[0] == 'f'){

                     int v1=0,n1=0,v2=0,n2=0,v3=0,n3=0;
                     fscanf(file, "%d//%d %d//%d %d//%d\n", &v1, &n1, &v2, &n2, &v3,&n3);
                     Face f;
                     f.iv1 = v1;
                     f.iv2 = v2;
                     f.iv3 = v3;
                     f.in1 = n1;
                     f.in2 = n2;
                     f.in3 = n3;
                     faces.push_back(f);
                     grafo.lista[f.iv1].push_back(f.iv2);
                     grafo.lista[f.iv1].push_back(f.iv3);
                     grafo.lista[f.iv2].push_back(f.iv1);
                     grafo.lista[f.iv3].push_back(f.iv1);
                     grafo.lista[f.iv2].push_back(f.iv3);
                     grafo.lista[f.iv3].push_back(f.iv2);

		 }

             }


            /* for(int h=1;h<grafo.lista.size();h++){

                cout<<"Vertice: "<<h<<" Vizinhos: "<<grafo.lista[h].size()<<endl;

             }*/


        }

        zerarBool();
        return true;
}
/*
GLfloat dot_multi(vec3 v1, vec3 v2){

  GLfloat x = v1.x * v2.x;
  GLfloat y = v1.y * v2.y;
  GLfloat z = v1.z * v2.z;

  return abs(x+y+z);
}*/

//GLfloat dot_multi(vec3 v1, GLfloat v2x, GLfloat v2y,GLfloat v2z){
GLfloat dot_multi(vec3 v1, vec3 v2){
GLfloat x = v1.x * v2.x;
GLfloat y = v1.y * v2.y;
GLfloat z = v1.z * v2.z;

  return abs(x+y+z);
}

bool inside_Cube(vec3 p){

    /*
    cube3d  =  numpy array of the shape (8,3) with coordinates in the clockwise order. first the bottom plane is considered then the top one.
    points = array of points with shape (N, 3).

    Returns the indices of the points array which are outside the cube3d
    """
    b1,b2,b3,b4,t1,t2,t3,t4 = cube3d
    */
    vec3 dir1;
    dir1.x = (pontoCubo[2].x - pontoCubo[3].x);
    dir1.y = (pontoCubo[2].y - pontoCubo[3].y);
    dir1.z = (pontoCubo[2].z - pontoCubo[3].z);

    GLfloat size1 = sqrt(pow(dir1.x,2) + pow(dir1.y,2) + pow(dir1.z,2));

    dir1.x = dir1.x/size1;
    dir1.y = dir1.y/size1;
    dir1.z = dir1.z/size1;

    vec3 dir2;
    dir2.x = (pontoCubo[4].x - pontoCubo[3].x);
    dir2.y = (pontoCubo[4].y - pontoCubo[3].y);
    dir2.z = (pontoCubo[4].z - pontoCubo[3].z);

    GLfloat size2 = sqrt(pow(dir2.x,2) + pow(dir2.y,2)
 + pow(dir2.z,2));

    dir2.x = dir2.x/size2;
    dir2.y = dir2.y/size2;
    dir2.z = dir2.z/size2;

    vec3 dir3;
    dir3.x = (pontoCubo[0].x - pontoCubo[3].x);
    dir3.y = (pontoCubo[0].y - pontoCubo[3].y);
    dir3.z = (pontoCubo[0].z - pontoCubo[3].z);

    GLfloat size3 = sqrt(pow(dir3.x,2) + pow(dir3.y,2) + pow(dir3.z,2));

    dir3.x = dir3.x/size3;
    dir3.y = dir3.y/size3;
    dir3.z = dir3.z/size3;

    vec3 cube3d_center;
    cube3d_center.x = (pontoCubo[3].x + pontoCubo[6].x)/2.0;
    cube3d_center.y = (pontoCubo[3].y + pontoCubo[6].y)/2.0;
    cube3d_center.z = (pontoCubo[3].z + pontoCubo[6].z)/2.0;

    vec3 dir_vec;
    dir_vec.x = (p.x - cube3d_center.x);
    dir_vec.y = (p.y - cube3d_center.y);
    dir_vec.z = (p.z - cube3d_center.z);

    int res1;
    int res2;
    int res3;

    res1 = dot_multi(dir_vec, dir1);
    res1 = abs(res1*1);

    res2 = dot_multi(dir_vec, dir2);
    res2 = abs(res2*1);

    res3 = dot_multi(dir_vec, dir3);
    res3 = abs(res3*1);

    if(res1 <= size1 && res2 <= size2 && res3 <= size3){
    //if(res1 <= size1 ){
      //cout<<"ponto ver: x = "<<p.x<<" y= "<<p.y<<" z= "<<p.z<<endl;
      //cout<<"cube center: x = "<<cube3d_center.x<<" y= "<<cube3d_center.y<<" z= "<<cube3d_center.z<<endl;
      //cout<<"dir_vec x = "<<dir_vec.x<<" y= "<<dir_vec.y<<" z= "<<dir_vec.z<<endl<<endl;
      //cout<<"ponto cubo x = "<<pontoCubo[2].x<<" - "<<pontoCubo[3].x<<endl;
      //cout<<"dir1 x = "<<dir1x<<" y= "<<dir1y<<" z= "<<dir1z<<endl;
      //cout<<"dir2 x = "<<dir2.x<<" y= "<<dir2.y<<" z= "<<dir2.z<<endl;
      //cout<<"dir3 x = "<<dir3.x<<" y= "<<dir3.y<<" z= "<<dir3.z<<endl;

      //cout<<"res1 = "<<res1<<endl;
      //cout<<"res2 = "<<res2<<endl;
      //cout<<"res3 = "<<res3<<endl<<endl;

      //cout<<"size1 = "<<size1<<endl;
      //cout<<"size2 = "<<size2<<endl;
      //cout<<"size3 = "<<size3<<endl;
      return true;
      //getchar();
    }


    return false;
}


GLfloat calculaPiramide(vec3 b1, vec3 b2, vec3 t1, vec3 t2, vec3 p){

  vec3 cube3d_center;
  cube3d_center.x = (pontoCubo[3].x + pontoCubo[6].x)/(2.0f);
  cube3d_center.y = (pontoCubo[3].y + pontoCubo[6].y)/(2.0f);
  cube3d_center.z = (pontoCubo[3].z + pontoCubo[6].z)/(2.0f);

  //área da face b1 b2 t1 t2
  //pontoCubo[3]  //b1
  //pontoCubo[4]  //b2
  //pontoCubo[2]  //t1
  //pontoCubo[5]  //t2

  //b1 para b2
  GLfloat f1_dist_1 = sqrt(pow(b1.x - b2.x,2) + pow(b1.y - b2.y,2) + pow(b1.z - b2.z,2));

  //b1 para t1
  GLfloat f1_dist_2 = sqrt(pow(b1.x - t1.x,2) + pow(b1.y - t1.y,2) + pow(b1.z - t1.z,2));

  GLfloat f1_area_base = f1_dist_1*f1_dist_2;

  //ponto central da face
  vec3 f1_central;
  f1_central.x = (b1.x + t2.x)/2.0;
  f1_central.y = (b1.y + t2.y)/2.0;
  f1_central.z = (b1.z + t2.z)/2.0;

  //face central para centro do cubo - altura
  GLfloat f1_dist_3 = sqrt(pow(f1_central.x - p.x,2) + pow(f1_central.y - p.y,2) + pow(f1_central.z - p.z,2));

  //apótema da base da piramide
  vec3 f1_apo;
  f1_apo.x = (b1.x + b2.x)/(2.0f);
  f1_apo.y = (b1.y + b2.y)/(2.0f);
  f1_apo.z = (b1.z + b2.z)/(2.0f);

  GLfloat f1_dist_4 = sqrt(pow(f1_central.x - f1_apo.x,2) + pow(f1_central.y - f1_apo.y,2) + pow(f1_central.z - f1_apo.z,2));

  GLfloat f1_area_apo = (sqrt(pow(f1_dist_4, 2)+pow(f1_dist_3, 2)));

  GLfloat f1_area_face = (f1_area_apo + f1_dist_1)*2;

  return f1_area_face + f1_area_base;

}

bool inside_Cube2(vec3 p){

  vec3 dir1;
  dir1.x = (pontoCubo[2].x - pontoCubo[3].x);
  dir1.y = (pontoCubo[2].y - pontoCubo[3].y);
  dir1.z = (pontoCubo[2].z - pontoCubo[3].z);/*
  cout<<"ponto 2: x = "<<pontoCubo[2].x<< " y = "<<pontoCubo[2].y<<" z = "<<pontoCubo[2].z<<endl;
  cout<<"ponto 3: x = "<<pontoCubo[3].x<< " y = "<<pontoCubo[3].y<<" z = "<<pontoCubo[3].z<<endl;
  cout<<"dir1: x = "<<pontoCubo[2].x - pontoCubo[3].x<< " y = "<<pontoCubo[2].y - pontoCubo[3].y<<" z = "<<pontoCubo[2].z - pontoCubo[3].z<<endl;*/

  GLfloat size1 = sqrt(pow(dir1.x,2) + pow(dir1.y,2) + pow(dir1.z,2));

  //cout<<"size1 = "<<size1<<endl<<endl;

  vec3 dir2;
  dir2.x = (pontoCubo[4].x - pontoCubo[3].x);
  dir2.y = (pontoCubo[4].y - pontoCubo[3].y);
  dir2.z = (pontoCubo[4].z - pontoCubo[3].z);/*
  cout<<"ponto 4: x = "<<pontoCubo[4].x<< " y = "<<pontoCubo[4].y<<" z = "<<pontoCubo[4].z<<endl;
  cout<<"ponto 3: x = "<<pontoCubo[3].x<< " y = "<<pontoCubo[3].y<<" z = "<<pontoCubo[3].z<<endl;
  cout<<"dir2: x = "<<pontoCubo[4].x - pontoCubo[3].x<< " y = "<<pontoCubo[4].y - pontoCubo[3].y<<" z = "<<pontoCubo[4].z - pontoCubo[3].z<<endl;*/

  GLfloat size2 = sqrt(pow(dir2.x,2) + pow(dir2.y,2) + pow(dir2.z,2));

  //cout<<"size2 = "<<size2<<endl<<endl;

  vec3 dir3;
  dir3.x = (pontoCubo[0].x - pontoCubo[3].x);
  dir3.y = (pontoCubo[0].y - pontoCubo[3].y);
  dir3.z = (pontoCubo[0].z - pontoCubo[3].z);/*
  cout<<"ponto 0: x = "<<pontoCubo[0].x<< " y = "<<pontoCubo[0].y<<" z = "<<pontoCubo[0].z<<endl;
  cout<<"ponto 3: x = "<<pontoCubo[3].x<< " y = "<<pontoCubo[3].y<<" z = "<<pontoCubo[3].z<<endl;
  cout<<"dir3: x = "<<pontoCubo[0].x - pontoCubo[3].x<< " y = "<<pontoCubo[0].y - pontoCubo[3].y<<" z = "<<pontoCubo[0].z - pontoCubo[3].z<<endl;*/

  GLfloat size3 = sqrt(pow(dir3.x,2) + pow(dir3.y,2) + pow(dir3.z,2));

  //cout<<"size3 = "<<size3<<endl<<endl;

  //área total do cubo
  GLfloat areaCube = size1*size2*size3;

  //cout<<"areaCube = "<<areaCube<<endl<<endl;

  vec3 cube3d_center;
  cube3d_center.x = (pontoCubo[3].x + pontoCubo[6].x)/2.0;
  cube3d_center.y = (pontoCubo[3].y + pontoCubo[6].y)/2.0;
  cube3d_center.z = (pontoCubo[3].z + pontoCubo[6].z)/2.0;


  //pontoCubo[3]  //b1
  //pontoCubo[4]  //b2
  //pontoCubo[7]  //b3
  //pontoCubo[0]  //b4
  //pontoCubo[2]  //t1
  //pontoCubo[5]  //t2
  //pontoCubo[6]  //t3
  //pontoCubo[1]  //t4

  //área da face b1 b2 t1 t2
  GLfloat f1_area = calculaPiramide(pontoCubo[3], pontoCubo[4], pontoCubo[2], pontoCubo[5], p);
  //cout<<"f1 area = "<<f1_area<<endl;

  //área da face b2 b3 t2 t3
  GLfloat f2_area = calculaPiramide(pontoCubo[4], pontoCubo[7], pontoCubo[5], pontoCubo[6], p);

  //área da face b3 b4 t3 t4
  GLfloat f3_area = calculaPiramide(pontoCubo[7], pontoCubo[0], pontoCubo[6], pontoCubo[1], p);

  //área da face b4 b1 t4 t1
  GLfloat f4_area = calculaPiramide(pontoCubo[0], pontoCubo[3], pontoCubo[1], pontoCubo[2], p);

  //área da face b1 b2 b3 b4
  GLfloat f5_area = calculaPiramide(pontoCubo[3], pontoCubo[4], pontoCubo[7], pontoCubo[0], p);

  //área da face t1 t2 t3 t4
  GLfloat f6_area = calculaPiramide(pontoCubo[2], pontoCubo[5], pontoCubo[6], pontoCubo[1], p);

  GLfloat f_piramide = f1_area + f2_area + f3_area + f4_area + f5_area + f6_area;



  if(f_piramide <= areaCube){

    cout<<"area cubo = "<<areaCube<<endl;
    cout<<"area piramide total = "<<f_piramide<<endl<<endl;



    return true;
  }

  return false;
}

GLfloat inside_Cube3(vec3 p){
  //calcula distancia da diagonal do CUBO
  vec3 cube3d_center;
  cube3d_center.x = (pontoCubo[3].x + pontoCubo[6].x)/2.0;
  cube3d_center.y = (pontoCubo[3].y + pontoCubo[6].y)/2.0;
  cube3d_center.z = (pontoCubo[3].z + pontoCubo[6].z)/2.0;

  GLfloat dist_diag = sqrt(pow((pontoCubo[3].x - pontoCubo[6].x),2) + pow((pontoCubo[3].y - pontoCubo[6].y),2) + pow((pontoCubo[3].z - pontoCubo[6].z),2));

  GLfloat dist_p0 = sqrt(pow((pontoCubo[0].x - p.x),2) + pow((pontoCubo[0].y - p.y),2) + pow((pontoCubo[0].z - p.z),2));
  GLfloat dist_p1 = sqrt(pow((pontoCubo[1].x - p.x),2) + pow((pontoCubo[1].y - p.y),2) + pow((pontoCubo[1].z - p.z),2));
  GLfloat dist_p2 = sqrt(pow((pontoCubo[2].x - p.x),2) + pow((pontoCubo[2].y - p.y),2) + pow((pontoCubo[2].z - p.z),2));
  GLfloat dist_p3 = sqrt(pow((pontoCubo[3].x - p.x),2) + pow((pontoCubo[3].y - p.y),2) + pow((pontoCubo[3].z - p.z),2));
  GLfloat dist_p4 = sqrt(pow((pontoCubo[4].x - p.x),2) + pow((pontoCubo[4].y - p.y),2) + pow((pontoCubo[4].z - p.z),2));
  GLfloat dist_p5 = sqrt(pow((pontoCubo[5].x - p.x),2) + pow((pontoCubo[5].y - p.y),2) + pow((pontoCubo[5].z - p.z),2));
  GLfloat dist_p6 = sqrt(pow((pontoCubo[6].x - p.x),2) + pow((pontoCubo[6].y - p.y),2) + pow((pontoCubo[6].z - p.z),2));
  GLfloat dist_p7 = sqrt(pow((pontoCubo[7].x - p.x),2) + pow((pontoCubo[7].y - p.y),2) + pow((pontoCubo[7].z - p.z),2));

  if(dist_p0 > dist_diag){
    return false;
  }
  if(dist_p1 > dist_diag){
    return false;
  }
  if(dist_p2 > dist_diag){
    return false;
  }
  if(dist_p3 > dist_diag){
    return false;
  }
  if(dist_p4 > dist_diag){
    return false;
  }
  if(dist_p5 > dist_diag){
    return false;
  }
  if(dist_p6 > dist_diag){
    return false;
  }
  if(dist_p7 > dist_diag){
    return false;
  }

  return true;
}


void separarObjeto(){

    normalsSeparado.clear();
    vertSeparado.clear();
    fSeparadoStruct.clear();
    vec3 t,u;
    normalsSeparado.push_back(t);
    vertSeparado.push_back(u);
    int cont=1;
     for(int i=0;i < faces.size();i++)
         fSeparadoBool[i]=0;


   for(int i=faces.size()-1; i>=0;i--){

         if(CUBO == true && inside_Cube3(vertices[faces[i].iv1]) && inside_Cube3(vertices[faces[i].iv2]) && inside_Cube3(vertices[faces[i].iv3])){

            vertSeparado.push_back(vec3(vertices[faces[i].iv1]));
            vertSeparado.push_back(vec3(vertices[faces[i].iv2]));
            vertSeparado.push_back(vec3(vertices[faces[i].iv3]));
            normalsSeparado.push_back(vec3(normals[faces[i].iv1]));
            normalsSeparado.push_back(vec3(normals[faces[i].iv2]));
            normalsSeparado.push_back(vec3(normals[faces[i].iv3]));

	    Face f;
            f.iv1 = cont;
            cont++;
 	    f.iv2 = cont;
            cont++;
            f.iv3 = cont;
            cont++;
            fSeparadoStruct.push_back(f);
            fSeparadoBool[i]=1;

        }


   }


  ofstream myfile;
  string nomeSeparado = "objSeparado"+to_string(contSeparado)+".obj";
  myfile.open (nomeSeparado);

  //write vertices
  for(int i=1;i<vertSeparado.size();i++)
    myfile << "v "<<vertSeparado[i].x<<" "<<vertSeparado[i].y<<" "<<vertSeparado[i].z<<"\n";

  //write normals
  for(int i=1;i<normalsSeparado.size();i++)
    myfile << "vn "<<normalsSeparado[i].x<<" "<<normalsSeparado[i].y<<" "<<normalsSeparado[i].z<<"\n";


  //write faces
  for(int i=0;i<fSeparadoStruct.size();i++)
    myfile << "f "<<fSeparadoStruct[i].iv1<<"//"<<fSeparadoStruct[i].iv1<<" "<<fSeparadoStruct[i].iv2<<"//"<<fSeparadoStruct[i].iv2<<" "<<fSeparadoStruct[i].iv3<<"//"<<fSeparadoStruct[i].iv3<<"\n";


  myfile.close();

          char * writable = new char[nomeSeparado.size() + 1];
	  std::copy(nomeSeparado.begin(), nomeSeparado.end(), writable);
	  writable[nomeSeparado.size()] = '\0'; // don't forget the terminating 0

  vertices.clear();
  normals.clear();
  rgb.clear();
  vec3 vert;
	vertices.push_back(vert);
  normals.push_back(vert);//para começar do indice 1
  rgb.push_back(vert);
	grafo.lista.clear();
    texture3d.clear();
    texture2d.clear();

	faces.clear();
          bool res = loadObjFromArchive(writable,'h');
         // desenharSala();

	  delete[] writable;



}

void desenharSala(){

        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glColor3f(0.0f, 0.0f, 1.0f);

        glBegin(GL_LINES);

    glLineWidth(2.0f);
    for(int i=-300;i<300;i=i+5){

        glColor3f(0.55,  0.55, 0.55);
        //desenhar na horizontal
	      glVertex3f(i,-5,300);
        glVertex3f(i,-5,-300);
          glColor3f(0.55,  0.55, 0.55 );
        //desenhar na vertical
        glVertex3f(300,-5,i);
        glVertex3f(-300,-5,i);
    }

    glEnd();

    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
       glPointSize(8);

    //desenha pontos de fronteira em vermelho
   if(!verticesDeFronteira.empty()){
     //glBegin(GL_LINE_STRIP);
     printf("vertices de fronteira not empty\n");
     for(int i=0;i<verticesDeFronteira.size();i++){

        //  cout<<"Pontos de fronteira: "<<vertices[verticesDeFronteira[i]]<<endl;

        glBegin(GL_POINTS);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(vertices[verticesDeFronteira[i]].x,vertices[verticesDeFronteira[i]].y,vertices[verticesDeFronteira[i]].z);
        //glVertex3f(vertices[sPoints.pointsFilteredTo3D[i].ind].x,vertices[sPoints.pointsFilteredTo3D[i].ind].y,vertices[sPoints.pointsFilteredTo3D[i].ind].z);
        glEnd();
     }

    // glEnd();

   }


        //cout<<"Quantidades de vertice: "<<vertices.size()<<endl;
        //cout<<"Quantidades de normals: "<<normals.size()<<endl;
        //cout<<"Quantidades de vertices com cores: "<<rgb.size()<<endl;
        //cout<<"Quantidades de faces: "<<faces.size()<<endl;

	//modo triangulo
  /*
  glEnable(GL_TEXTURE_3D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_3D, texName);
  glBegin(GL_TRIANGLES);
  */








  //cout<<"cubo: "<<CUBO<<endl;

	//cout <<" desenha invertido"<<endl;
	//for(int i=0;i<faces.size();i++){




//glColor3f(1.0f, 1.0f, 1.0f);
	for(int i=faces.size()-1; i>=0;i--){

        //if((fSeparadoBool[i] ==0  &&  !sep) ||(fSeparadoBool[i] ==1  &&  sep) ){

         //printf("%d\n", i);
         //cout << vertices[faces[i].iv1].x <<" "<< vertices[faces[i].iv1].y <<" "<< vertices[faces[i].iv1].z << endl;
         //cout<<"teste "<<i<<endl;
 //glEnable(GL_TEXTURE_2D);
 //glDisable(GL_TEXTURE_2D);



/*
         GLfloat un[3],vn[3];

         un[0] = vertices[faces[i].iv2].x-vertices[faces[i].iv1].x;un[1] = vertices[faces[i].iv2].y-vertices[faces[i].iv1].y;un[2] = vertices[faces[i].iv2].z-vertices[faces[i].iv1].z;
         vn[0] = vertices[faces[i].iv3].x-vertices[faces[i].iv1].x;vn[1] = vertices[faces[i].iv3].y-vertices[faces[i].iv1].y;vn[2] = vertices[faces[i].iv3].z-vertices[faces[i].iv1].z;
         GLfloat nox=0,noy=0,noz=0;
         nox = un[1]*vn[2] - un[2]*vn[1];
         noy = un[2]*vn[0] - un[0]*vn[2];
         noz = un[0]*vn[1] - un[1]*vn[0];
*/
         //glNormal3f(nox, noy, noz);

           //cout<<"cubo e true\n";
         //if(CUBO == true && textura == true && inside_Cube2(vertices[faces[i].iv1]) && inside_Cube2(vertices[faces[i].iv2]) && inside_Cube2(vertices[faces[i].iv3])){


         if(CUBO == true && textura == true && inside_Cube3(vertices[faces[i].iv1]) && inside_Cube3(vertices[faces[i].iv2]) && inside_Cube3(vertices[faces[i].iv3])){
           //cout<<"textura!\n";
         glEnable(GL_TEXTURE_2D);
         glBegin(GL_TRIANGLES);

        //
           glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
           //glBindTexture(GL_TEXTURE_2D, texName);

           texture2d[faces[i].iv1] = true;
           textureIndices[faces[i].iv1].x = 0.0;
           textureIndices[faces[i].iv1].y = 0.0;

           textureIndices[faces[i].iv2].x = 0.5;
           textureIndices[faces[i].iv2].y = 1.0;

           textureIndices[faces[i].iv3].x = 1.0;
           textureIndices[faces[i].iv3].y = 0.0;

           glTexCoord2f(textureIndices[faces[i].iv1].x, textureIndices[faces[i].iv1].y);
           glNormal3f(normals[faces[i].iv1].x,normals[faces[i].iv1].y,normals[faces[i].iv1].z);
  	       glVertex3f(vertices[faces[i].iv1].x,vertices[faces[i].iv1].y,vertices[faces[i].iv1].z);


           glTexCoord2f(textureIndices[faces[i].iv2].x, textureIndices[faces[i].iv2].y);
           glNormal3f(normals[faces[i].iv2].x,normals[faces[i].iv2].y,normals[faces[i].iv2].z);
           glVertex3f(vertices[faces[i].iv2].x,vertices[faces[i].iv2].y,vertices[faces[i].iv2].z);


           glTexCoord2f(textureIndices[faces[i].iv3].x, textureIndices[faces[i].iv3].y);
           glNormal3f(normals[faces[i].iv3].x,normals[faces[i].iv3].y,normals[faces[i].iv3].z);
  	       glVertex3f(vertices[faces[i].iv3].x,vertices[faces[i].iv3].y,vertices[faces[i].iv3].z);
           //getchar();

          // glDisable(GL_TEXTURE_2D);
           glEnd();
           glDisable(GL_TEXTURE_2D);

         }

         else if(texture2d[faces[i].iv1] == true){
           //if(textura == false){cout<<"texture 2d\n";}

           glEnable(GL_TEXTURE_2D);
           glBegin(GL_TRIANGLES);

          //
           glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
           //glBindTexture(GL_TEXTURE_2D, texName);

           glTexCoord2f(textureIndices[faces[i].iv1].x, textureIndices[faces[i].iv1].y);
           glNormal3f(normals[faces[i].iv1].x,normals[faces[i].iv1].y,normals[faces[i].iv1].z);
  	       glVertex3f(vertices[faces[i].iv1].x,vertices[faces[i].iv1].y,vertices[faces[i].iv1].z);


           glTexCoord2f(textureIndices[faces[i].iv2].x, textureIndices[faces[i].iv2].y);
           glNormal3f(normals[faces[i].iv2].x,normals[faces[i].iv2].y,normals[faces[i].iv2].z);
           glVertex3f(vertices[faces[i].iv2].x,vertices[faces[i].iv2].y,vertices[faces[i].iv2].z);


           glTexCoord2f(textureIndices[faces[i].iv3].x, textureIndices[faces[i].iv3].y);
           glNormal3f(normals[faces[i].iv3].x,normals[faces[i].iv3].y,normals[faces[i].iv3].z);
  	       glVertex3f(vertices[faces[i].iv3].x,vertices[faces[i].iv3].y,vertices[faces[i].iv3].z);
           //getchar();

          // glDisable(GL_TEXTURE_2D);
           glEnd();
           glDisable(GL_TEXTURE_2D);


         }

         else if(texture3d[faces[i].iv1] == true){

           glEnable(GL_TEXTURE_2D);
           glBegin(GL_TRIANGLES);

          //
           glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
           //glBindTexture(GL_TEXTURE_2D, texName);

           glTexCoord3f(textureIndices[faces[i].iv1].x, textureIndices[faces[i].iv1].y, textureIndices[faces[i].iv1].z);
           glNormal3f(normals[faces[i].iv1].x,normals[faces[i].iv1].y,normals[faces[i].iv1].z);
  	       glVertex3f(vertices[faces[i].iv1].x,vertices[faces[i].iv1].y,vertices[faces[i].iv1].z);


           glTexCoord3f(textureIndices[faces[i].iv2].x, textureIndices[faces[i].iv2].y, textureIndices[faces[i].iv1].z);
           glNormal3f(normals[faces[i].iv2].x,normals[faces[i].iv2].y,normals[faces[i].iv2].z);
           glVertex3f(vertices[faces[i].iv2].x,vertices[faces[i].iv2].y,vertices[faces[i].iv2].z);


           glTexCoord3f(textureIndices[faces[i].iv3].x, textureIndices[faces[i].iv3].y, textureIndices[faces[i].iv1].z);
           glNormal3f(normals[faces[i].iv3].x,normals[faces[i].iv3].y,normals[faces[i].iv3].z);
  	       glVertex3f(vertices[faces[i].iv3].x,vertices[faces[i].iv3].y,vertices[faces[i].iv3].z);
           //getchar();

          // glDisable(GL_TEXTURE_2D);
           glEnd();
           glDisable(GL_TEXTURE_2D);


         }

         else{

           if(i == 1){
             //cout << "cor teste: " << rgb[faces[i].iv1].x << " " << rgb[faces[i].iv1].y << " " << rgb[faces[i].iv1].z <<endl;
           }
           glBegin(GL_TRIANGLES);
              //glEnable(GL_TEXTURE_2D);
           glColor3f(rgb[faces[i].iv1].x,rgb[faces[i].iv1].y,rgb[faces[i].iv1].z);
           //glColor3f(0.4f, 0.4f, 0.4fa);
           glNormal3f(normals[faces[i].iv1].x,normals[faces[i].iv1].y,normals[faces[i].iv1].z);
           glVertex3f(vertices[faces[i].iv1].x,vertices[faces[i].iv1].y,vertices[faces[i].iv1].z);

           glColor3f(rgb[faces[i].iv2].x,rgb[faces[i].iv2].y,rgb[faces[i].iv2].z);
           //glColor3f(0.4f, 0.4f, 0.4f);
           glNormal3f(normals[faces[i].iv2].x,normals[faces[i].iv2].y,normals[faces[i].iv2].z);
           glVertex3f(vertices[faces[i].iv2].x,vertices[faces[i].iv2].y,vertices[faces[i].iv2].z);

           glColor3f(rgb[faces[i].iv3].x,rgb[faces[i].iv3].y,rgb[faces[i].iv3].z);
           //glColor3f(0.4f, 0.4f, 0.4f);
           glNormal3f(normals[faces[i].iv3].x,normals[faces[i].iv3].y,normals[faces[i].iv3].z);
           glVertex3f(vertices[faces[i].iv3].x,vertices[faces[i].iv3].y,vertices[faces[i].iv3].z);

           //glDisable(GL_TEXTURE_2D);
           glEnd();

           /*
          // glEnable(GL_TEXTURE_2D);
           glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
           //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
           glBindTexture(GL_TEXTURE_2D, texName);

           glTexCoord2f(0.0, 0.0);
           glNormal3f(normals[faces[i].iv1].x,normals[faces[i].iv1].y,normals[faces[i].iv1].z);
  	       glVertex3f(vertices[faces[i].iv1].x,vertices[faces[i].iv1].y,vertices[faces[i].iv1].z);


           glTexCoord2f(0.5, 1.0);
           glNormal3f(normals[faces[i].iv2].x,normals[faces[i].iv2].y,normals[faces[i].iv2].z);
           glVertex3f(vertices[faces[i].iv2].x,vertices[faces[i].iv2].y,vertices[faces[i].iv2].z);


           glTexCoord2f(1.0, 0.0);
           glNormal3f(normals[faces[i].iv3].x,normals[faces[i].iv3].y,normals[faces[i].iv3].z);
  	       glVertex3f(vertices[faces[i].iv3].x,vertices[faces[i].iv3].y,vertices[faces[i].iv3].z);
           //getchar();

           //glDisable(GL_TEXTURE_2D);
            */


             //}//endif
         }//endfor


  }

  if(CUBO){

      desenharCubo();

  }else if(ESFERA){

      desenharEsfera();

  }else if(PIRAMIDE){


  }

	glutSwapBuffers();
     	//glutPostRedisplay();

}
