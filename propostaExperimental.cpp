//#include <fstream>
void realizarPropostaExperimental(string path,string nameOfText,int range){
    //projection[sPoints.pointsFilteredTo3D[i].ind]; acessaar os pontos de fronteira projetados na tela (pontos 2D)
    /* ofstream out(nameOfText);
    for(int i=0;i<sPoints.pointsFilteredTo3D.size();i++){

         GLfloat x = projection[sPoints.pointsFilteredTo3D[i].ind].points.x;
         GLfloat y = projection[sPoints.pointsFilteredTo3D[i].ind].points.y;
         GLfloat z = projection[sPoints.pointsFilteredTo3D[i].ind].points.z;
        out <<x<< " "<<y<<" "<<z<<"\n";

    }
	  out.close();*/

    string parametro = "python3 canny.py "+path+" "+nameOfText+" "+to_string(range);
    system(parametro.c_str());

}
