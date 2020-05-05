

void readFileBoundingBox(char * path){

   FILE * file = fopen(path, "r");

   if( file == NULL){

        printf("Not possible to read the file, please verify if it's an obj type");
        return;

	}

 int left=0;
 int top=0;
 int width=0;
 int height=0;

  while(1){

    char lineHeader[500];
    int res = fscanf (file,"%s",lineHeader);

    if(res == EOF){

       break;

    }

    //cout<<"Apareci aqui: "<<lineHeader<<endl;
    if(lineHeader[0] == '(' && lineHeader[1] == 'l' && lineHeader[2] == 'e'){


              left = 1;

    }else if(left == 1){
      //cout<<"Entrei aqui:"<<lineHeader<<endl;
      fscanf(file, "%d",&bBox.left);

       int cont=0;
       int index=1;
       for(int j=0;lineHeader[j]!='\0';j++){

          cont=cont*index + lineHeader[j]-'0';
          index=10;
       }


      //cout<<"Informacao: "<<bBox.left<<" "<<bBox.top<<" "<<bBox.width<<" "<<bBox.height<<endl;
      left = 0;

      bBox.left = cont;
      //cout<<"gheuirhguigerh: "<<cont<<endl;

    }else if(lineHeader[0] == 't' && lineHeader[1] == 'o' && lineHeader[2] == 'p'){

              top=1;

    }else if(top == 1){

      fscanf(file, "%d\n",&bBox.top);
      //cout<<"Informacao: "<<bBox.left<<" "<<bBox.top<<" "<<bBox.width<<" "<<bBox.height<<endl;

      int cont=0;
      int index=1;
      for(int j=0;lineHeader[j]!='\0';j++){

         cont=cont*index + lineHeader[j]-'0';
         index=10;
      }

      bBox.top = cont;
      top = 0;

    }else if(lineHeader[0] == 'w' && lineHeader[1] == 'i' && lineHeader[2] == 'd'){

             width=1;

    }else if(width == 1){

      fscanf(file, "%d\n",&bBox.width);
      //cout<<"Informacao: "<<bBox.left<<" "<<bBox.top<<" "<<bBox.width<<" "<<bBox.height<<endl;

      int cont=0;
      int index=1;
      for(int j=0;lineHeader[j]!='\0';j++){

         cont=cont*index + lineHeader[j]-'0';
         index=10;
      }

      bBox.width = cont;
      width = 0;

    }else if(lineHeader[0] == 'h' && lineHeader[1] == 'e' && lineHeader[2] == 'i'){

             height=1;

    }else if(height == 1){

      fscanf(file, "%d\n",&bBox.height);

      int cont=0;
      int index=1;
      for(int j=0;lineHeader[j]!=')';j++){

         cont=cont*index + lineHeader[j]-'0';
         index=10;
      }

      bBox.height = cont;
      height = 0;

    }


  }

    //cout<<"Informacao: "<<bBox.left<<" "<<bBox.top<<" "<<bBox.width<<" "<<bBox.height<<endl;

}
