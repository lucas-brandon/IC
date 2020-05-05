#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <iostream>


using namespace std;

// Variáveis
char texto[30];
GLfloat win;
GLint view_w, view_h, primitiva;


// Desenha um texto na janela GLUT
void DesenhaTexto(char *string)
{
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(-win,win-(win*0.08));
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++);
	glPopMatrix();
}

// Gerenciamento do menu com as opções de cores
void MenuPrimitiva(int op)
{
   switch(op) {
            case 0:
                     inicializaPontosCubo();
                     CUBO = !CUBO;
                     break;
            case 1:
                     inicializaPontosEsfera();
                     ESFERA = !ESFERA;
                     break;
            case 2:
                     PIRAMIDE  = !PIRAMIDE;
                     break;
    }
    glutPostRedisplay();
}


void Selecao(int op)
{
   switch(op) {
            case 0:
                     selecionarSala = true;
                     selecionarBounding = false;
                     selecionarCena = false;
                     break;
            case 1:
                     selecionarCena = false;
                     selecionarSala = false;
                     selecionarBounding = true;
                     break;
            case 2:
                     selecionarCena = true;
                     selecionarSala = false;
                     selecionarBounding = false;
                     break;

    }
    glutPostRedisplay();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op)
{


}

// Criacao do Menu
void CriaMenu()
{
    int menu,submenu1,submenu2;

    submenu1 = glutCreateMenu(MenuPrimitiva);
    glutAddMenuEntry("Cubo",0);
    glutAddMenuEntry("Esfera",1);
    glutAddMenuEntry("Piramide",2);

  submenu2 = glutCreateMenu(Selecao);
    glutAddMenuEntry("Selecionar Objeto",0);
    glutAddMenuEntry("Selecionar Bounding Boxe",1);
    glutAddMenuEntry("Selecionar cena",2);


    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Bounding Boxes",submenu1);
    glutAddSubMenu("Selecionar",submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
