
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif


#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
#include <vector>
#include <math.h>
#include <errno.h>
#include <fenv.h>
#include <ctime>
#include <time.h>
int atoi(const char *string);
int phWidth = 500;
int phHeight = 500;
int logWidth = 100;
int logHeight =100;
int cx=50,cy=50;
int width =20;
int D= cx-(width/2);
int E= cy+(width/2);
int alphaX=0, alphaY=0;
int  x,y;
int boxes[20];
int score=0;


void keyboardPP(int keypp,int x,int y)
{
    if(keypp==GLUT_KEY_UP)    cy+=5;
    if(keypp==GLUT_KEY_DOWN)  cy-=5;
    if(keypp==GLUT_KEY_RIGHT) cx+=5;
    if(keypp==GLUT_KEY_LEFT)  cx-=5;
    glutPostRedisplay();


}


void init2D(float r, float g, float b){
    glClearColor(r,g,b,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,logHeight,0.0,logWidth);
}



void PrintSome(char *str,int x,int y) {
glColor3f (1, 1, 1);
glRasterPos2d(x,y);
for (int i=0;i<strlen(str);i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
glFlush();
}

void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,logWidth,0.0,logHeight);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    for(int i=0;i<20;i+=2){
            glBegin(GL_POLYGON);
            glVertex2i(boxes[i]-1,boxes[i+1]-1);
            glVertex2i(boxes[i]-1,boxes[i+1]+1);
            glVertex2i(boxes[i]+1,boxes[i+1]+1);
            glVertex2i(boxes[i]+1,boxes[i+1]-1);
            glEnd();
    }
    for(int i=0;i<20;i+=2){
        if(boxes[i]>=(cx-10) && boxes[i]<=(cx+10) && boxes[i+1]>=(cy-10) && boxes[i+1]<=(cy+10))
        {
            boxes[i]=500;
            score++;
        }
    }
        
    glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2i(cx-(width/2)+alphaX,cy-(width/2)+alphaY);
        glColor3f(1,0,0);
        glVertex2i(cx-(width/2)+alphaX,cy+(width/2)+alphaY);
        glColor3f(1,0,1);
        glVertex2i(cx+(width/2)+alphaX,cy+(width/2)+alphaY);
        glColor3f(1,1,1);
        glVertex2i(cx+(width/2)+alphaX,cy-(width/2)+alphaY);
        glEnd();
    glColor3f(0,0,0);
    PrintSome("score= ",5,95);
    char buff[10];
            printSome(itoa(score,buff,10),20,95);
            
        
        glutSwapBuffers();
        glFlush();


}

int main (int argc, char*argv[])
{
    srand(time(0));
        for(int i=0;i<20;i+=2){
            boxes[i]=rand()%100;
            boxes[i+1]=rand()%100;
    }
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(phWidth,phHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("BIG SQUARE EATS SMALL SQUARES GAME");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboardPP);
    glutMainLoop();

}
