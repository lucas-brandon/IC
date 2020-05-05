#include <cstdlib>
#include "glm/vec2.hpp"
#include <vector>
#include <list>
#include "glm/vec3.hpp"
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;
using glm::vec3;
//Os define da vida
bool CUBO =  false;
bool ESFERA =  false;
bool PIRAMIDE =  false;
bool textura = false;
bool selecionarSala = false;
bool selecionarBounding = false;
bool selecionarCena = false;
GLfloat indiceEixoX=0;
GLfloat indiceEixoY=0;
vector<vec3> pontoCubo(8);
vector<vector<vec3> > pontoEsfera;
vector<vec3> pontoPiramide;
vector<vec3> pontoCameraEixoX;
vector<vec3> pontoCameraEixoY;
GLfloat angle=60, fAspect;
GLfloat r=0;
GLfloat l=0;
GLfloat top=0;
GLfloat bottom=0;
GLfloat near, far;
GLint pg=0;
string nomeImagem;
int contImagem=0;
GLint widthFrame = 640;
GLint heightFrame = 480;
bool toZero = false;
vector< unsigned int > vertexIndices, uvIndices, normalIndices;
vector<vec3> vertices;
vector<vec3> vertSeparado;
vector<vec3> normalsSeparado;
vector<vec3> normals;
vector<vec3> rgb;
vector<vec3> textureIndices;
vector<bool> texture2d;
vector<bool> texture3d;
bool sep=false;
//Estruturas para armazenar os pontos de um objeto dentro de um bounding box:
vector<vec3> vt;
vector<vec3> nt;
vector<vec3> rgbt;

vector<GLuint> ind;
vector<int> verticesDeFronteira;
int contadorDeArquivosText=0;


GLfloat motion=0;
bool press=false;

GLfloat contRotationX = 0;
GLfloat contRotationY = 0;
GLfloat contRotationZ = 0;

// angle of rotation for the camera direction
float anglee=0.0,angley=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;


static GLubyte checkImage[64][64][4];

static GLuint texName[10];

void makeCheckImage(void)
{
   int i, j, c;

   for (i = 0; i < 64; i++) {
      for (j = 0; j < 64; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

int img_width, img_height, img_nrChannels;
int img_width1, img_height1, img_nrChannels1;
//unsigned char *data = stbi_load("ex09.jpeg", &img_width, &img_height, &img_nrChannels, 0);
unsigned char *data = stbi_load("blue_texture.jpg", &img_width, &img_height, &img_nrChannels, 0);
unsigned char *data1 = stbi_load("green_texture.jpg", &img_width1, &img_height1, &img_nrChannels1, 0);


class Grafo{

public:
  vector<list<int> > lista;

  Grafo(){}

  void preencherGrafo(int size){

      for(int i=0;i<=size;i++){

          list<int> v;
          lista.push_back(v);
      }

  }

};

class StructureToProjection{

public:
  vec3 points;
  int ind;

};

class StructureSiftPoints{

public:
  vector<vec3> pointsWithNoFilter;
  vector<StructureToProjection> pointsFilteredTo3D;


};
class StructureBoundingBox{

  public:
    int left;
    int top;
    int width;
    int height;


};

StructureSiftPoints sPoints;
StructureBoundingBox bBox;
vector<StructureToProjection> projection;
Grafo grafo;
