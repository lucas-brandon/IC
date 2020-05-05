#include <cmath>
#include <vector>
using namespace std;
using glm::vec3;



void calculaMatrizDeProjecao(GLfloat px,GLfloat py,GLfloat pz, int index){

  GLfloat A,B;
  GLfloat psx,psy,psz;

   /*if(pz ==0.0f)
       pz = 0.01f;*/

  /**/
  A = -((far+near)/(far-near));
  B = -((2*far*near)/(far-near));

  //cout<<"A: "<<A<<" B: "<<B<<endl;

  psz = (A*pz + B)/(-pz);
  psy = (2*near*py)/(-pz*(top-bottom)) - ((top+bottom)/(top-bottom));
  psx = (2*near*px)/(-pz*(r-l)) - ((r+l)/(r-l));

  /*
  GLfloat mp[4][4] = {
      {2*near/(r-l),0,(r+l)/(r-l),0},
      {0,2*near/(top-bottom),(top+bottom)/(top-bottom),0},
      {0,0,-(far+near)/(far-near),-(2*far*near)/(far-near)},
      {0,0,-1,0},
      };

      psx = px*mp[0][0] + py*mp[1][0] + pz*mp[2][0] + mp[3][0];
      psy = px*mp[0][1] + py*mp[1][1] + pz*mp[2][1] + mp[3][1];
      psz = px*mp[0][2] + py*mp[1][2] + pz*mp[2][2] + mp[3][2];

    */
  //cout<<"r: "<<r<<" l: "<<l<<endl;
  //cout<<"x: "<<psx*widthFrame/2<<" y: "<<psy*heightFrame/2<<" z: "<<psz<<endl;


  StructureToProjection pro;

  pro.ind = index;
  pro.points = vec3 (psx*widthFrame/2,psy*heightFrame/2,psz);
  projection.push_back(pro);

  


}
void calculaCantos(GLfloat w,GLfloat h){

 GLfloat asp;
 asp = w/h;

 top = tan(60 * 0.5 * M_PI / 180)*near;
 bottom = -top;
 r = top*asp;
 l = -top*asp;
 //cout<<"r: "<<r<<" l: "<<l<<endl;

}
void setParametros(GLfloat n,GLfloat f){

   near=n;
   far=f;

}
