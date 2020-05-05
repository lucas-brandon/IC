#include <cmath>
#include <queue>

void filtarPontos(GLfloat range){
vector<StructureToProjection> mediaPontos;
   for(int i=0;i<sPoints.pointsWithNoFilter.size();i++){

        GLfloat minPoints = 1;
        StructureToProjection pro;



      for(int j=0;j<projection.size();j++){

          if(abs(sPoints.pointsWithNoFilter[i].x - projection[j].points.x) < range && abs(sPoints.pointsWithNoFilter[i].y - projection[j].points.y) < range && projection[j].points.z <= 1.0 ){


              if(minPoints > projection[j].points.z){

                 //cout<<"Pontos do sift: "<<sPoints.pointsWithNoFilter[i].x<<" "<<sPoints.pointsWithNoFilter[i].y<<" Pontos da projeção: "<<projection[j].points.x<<" "<<projection[j].points.y<<" "<<projection[j].points.z<<endl;
                  minPoints = projection[j].points.z;
                  //pro.points = vec3(vertices[projection[j].ind]);
                  //pro.ind = projection[j].ind;
                 pro.points = vec3(projection[j].points);
                 pro.ind = projection[j].ind;

              }

          }

      }

      //cout<<"pt final: "<<pro.points<<" "<<pro.ind<<endl;
       //cout<<"----------------------------------------------------------------"<<endl;
       //sPoints.pointsFilteredTo3D.push_back(pro);
       mediaPontos.push_back(pro);
   }

     GLfloat media=0;

    for(int i=0;i<mediaPontos.size();i++){

        media+=mediaPontos[i].points.z;


    }

    media=media/mediaPontos.size();


    for(int i=0;i<mediaPontos.size();i++){

        if(mediaPontos[i].points.z <= media){
            StructureToProjection pro;
          pro.points = vec3(vertices[mediaPontos[i].ind]);
          pro.ind = mediaPontos[i].ind;
          sPoints.pointsFilteredTo3D.push_back(pro);
        }

    }


}


void bfs(int in,queue<int>&adj,vector<int>&verificado,int tamCaminho,GLfloat limiar,vector<int>&dist){

list<int>::iterator it;


 for(it=grafo.lista[in].begin();it!=grafo.lista[in].end();it++){

    if(verificado[*it]!=1 && dist[in] != tamCaminho){

       verificado[*it]=1;

       GLfloat soma = abs((rgb[*it].x-rgb[in].x) + (rgb[*it].y-rgb[in].y) + (rgb[*it].z-rgb[in].z));

       if(soma < limiar){

           adj.push(*it);
           dist[*it] = dist[in]+1;

      }

      else{

           verticesDeFronteira.push_back(*it);

      }


    }

 }


  adj.pop();

}

void beginToBfs(int index,vector<int>&verificado,int tamCaminho,GLfloat limiar){

    queue<int> adj;
    vector<int>dist(vertices.size()+1,0);

    adj.push(index);

   while(!adj.empty()){

      int in = adj.front();
      bfs(in,adj,verificado,tamCaminho,limiar,dist);

   }


}

void encontrarFronteiras(){

   //encontrar os pontos mais proximos no arquivo
   filtarPontos(2.0f);

  //verticesDeFronteira.clear();
  vector<int> verificado(vertices.size()+1,0);

   //o algoritmo de cor funciona aqui
   for(int i=0;i<sPoints.pointsFilteredTo3D.size();i++){

       //cout<<"Vertices filtrados: "<<sPoints.pointsFilteredTo3D[i].points<<" cor"<<rgb[sPoints.pointsFilteredTo3D[i].ind]<<endl;

       beginToBfs(sPoints.pointsFilteredTo3D[i].ind,verificado,6,0.45f);


   }









}
