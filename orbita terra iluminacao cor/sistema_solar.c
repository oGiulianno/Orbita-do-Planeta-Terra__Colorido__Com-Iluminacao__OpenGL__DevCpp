/***************************************

Sistema solar iluminação
sistema_solar.c

Prof: Gustavo Vinhal

Alunos: GIULIANNO G LATORRACA
		VINICIUS HENRIQUE DA SILVA SOUZA

****************************************/

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat rotacaoX, rotacaoY, rotacaoZ;
GLdouble radius=2;

//intensidade das cores
GLfloat luzAmbiente[]={0.1, 0.1, 0.1, 1.0};
GLfloat luzDifusa[]={1, 1, 1, 1.0};
GLfloat luzEspecular[]={1.0, 1.0, 1.0, 1.0};
GLfloat comLuz[]={0.9, 0.9, 0.9, 0.01};
GLfloat semLuz[]={0.0, 0.0, 0.0, 1.0};

//cores
GLfloat corPreta[]={0.0, 0.0, 0.0, 1.0};
GLfloat corAzul[]={0.0, 0.0, 1.0, 0.0}; 
GLfloat corBranca[]={1.0, 1.0, 1.0, 1.0}; 
GLfloat corVermelha[]={1.0, 0.0, 0.0, 1.0}; 

GLfloat luzPosicao[]={0, 0, 0, 1};

void display(void);
void reshape(int x, int y);
 
void idleFunc(void){
	if(rotacaoZ > 360)
		rotacaoZ=rotacaoZ - 360.0*floor(rotacaoZ/360.0);

    if(rotacaoY > 360)
		rotacaoY=rotacaoY - 360.0*floor(rotacaoY/360.0); 

     rotacaoZ=rotacaoZ+0.10;
     rotacaoY=rotacaoY+0.10;
     
    display();
}
void inicializaLuminacao(){
    //liga luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //seta intensidade 
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

}
 
int main (int argc, char **argv){
    glutInit(&argc, argv); 
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(350,350);
    glutCreateWindow("sistema iluminação");
    inicializaLuminacao(); 

    rotacaoX = rotacaoY = rotacaoZ = 0.0;
    
    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
 
void display(void){
	
    glMatrixMode(GL_MODELVIEW);
    //apaga buffer de desenho
    glClear(GL_COLOR_BUFFER_BIT);
    //apaga matriz de identidade
    glLoadIdentity();
   
    glTranslatef(0.0,0.0,-20.0);
   
   	glPushMatrix();
     
    glTranslatef(0.0,0.0,0);
    //set as propriedades
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, corAzul);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, corAzul);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, corBranca);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2);
    glutSolidSphere(radius,25,25);
    
    glPopMatrix();

    glPushMatrix();
     
    glRotatef(rotacaoY,0.0,1.0,0.0);
    glTranslatef(5.0,0.0,0.0);
      
    //seta luz de posição
	glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, comLuz);   //Faaz a esfera brilhar
    glutSolidSphere(radius/2,45,45);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, semLuz);  

    glPopMatrix(); 

    glFlush();
    glutSwapBuffers();      
	 
}
 
void reshape(int x, int y){
    if (y == 0 || x == 0) 
		return;   
		
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,40.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}
