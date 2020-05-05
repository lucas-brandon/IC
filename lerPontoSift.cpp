void readPointsInTxt(char *path){


  FILE * file = fopen(path, "r");



        if( file == NULL){

            printf("Not possible to read the file, please verify if it's an obj type");
            return;

  	    }



        while(1){

             float x;
             float y;
             int ponteiroArquivo = fscanf(file, "%f %f\n", &x, &y);

            // cout<<"dasfsdfsgsd "<<contVerticeChar<<endl;

             if(ponteiroArquivo == EOF){

                 break;

            }

          //  float x;
          //  float y;
          //  fscanf(file, "%f %f\n", &x, &y);

            cout<<x<<" "<<y<<endl;

            sPoints.pointsWithNoFilter.push_back(vec3 (x,y,0));

       }

}
