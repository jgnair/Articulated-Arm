#include <iostream>
#include<gl/glu.h>
#include<GL/freeglut.h>

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

void display();
void reshape(int,int);
void keyboardInput(unsigned char,int,int);
void makeCylinder(int,int,int,int,int);
void makeSphere(double,int,int);
void updatePerspective(GLboolean toggle = GL_FALSE);

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Window 1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardInput);
    init();

    while(1){
        glutMainLoopEvent();
    }

    return 0;
}

float Shoulder_x_pos = 0.0;
float Shoulder_y_pos = 0.0;
float Shoulder_z_pos = 0.0;
int Upper_Arm_x_Angle = 0.0;
int Upper_Arm_y_Angle = 0.0;
int Upper_Arm_z_Angle = 0.0;
float Forearm_x_Angle = 0.0;
float Forearm_z_Angle = 0.0;
float Hand_x_Angle = 0.0;
float Hand_y_Angle = 0.0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Shoulder
    glPushMatrix();
    glTranslatef(Shoulder_x_pos-30.0,Shoulder_y_pos,Shoulder_z_pos-100.0);
    glRotatef(90.0,0.0,1.0,0.0);
    glColor3f(1.0,0.0,1.0);
    makeSphere(10.0,100,100);

    //Upper Arm
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    glRotatef(Upper_Arm_x_Angle,1.0,0.0,0.0);
    glRotatef(Upper_Arm_y_Angle,0.0,1.0,0.0);
    glRotatef(Upper_Arm_z_Angle,0.0,0.0,1.0);
    glColor3f(1.0,0.0,0.0);
    makeCylinder(5,4,30,50,1);

    //Forearm
    glPushMatrix();
    glTranslatef(0.0,0.0,29.0);
    glRotatef(Forearm_x_Angle,1.0,0.0,0.0);
    glRotatef(Forearm_z_Angle,0.0,0.0,1.0);
    glColor3f(0.0,1.0,0.0);
    makeCylinder(4,3,20,50,1);

    //Hand
    glPushMatrix();
    glTranslatef(0.0,0.0,19.0);
    glRotatef(Hand_x_Angle,1.0,0.0,0.0);
    glRotatef(Hand_y_Angle,0.0,1.0,0.0);
    glColor3f(0.0,0.0,1.0);
    makeCylinder(3,3,10,50,1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50,1,1.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void makeCylinder(int base, int top, int height, int slice, int stack){
    glBegin(GL_3D);
    GLUquadricObj *p = gluNewQuadric();
    gluCylinder(p,base,top,height,slice,stack);
}

void makeSphere(double radius, int slice, int stack){
    glBegin(GL_3D);
    GLUquadricObj *p = gluNewQuadric();
    gluSphere(p,radius,slice,stack);
}

void keyboardInput(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
            exit(0);
        case 'x':
            Shoulder_x_pos+=0.15;
            break;
        case 'X':
            Shoulder_x_pos-=0.15;
            break;
        case 'y':
            Shoulder_y_pos+=0.15;
            break;
        case 'Y':
            Shoulder_y_pos-=0.15;
            break;
        case 'z':
            Shoulder_z_pos+=0.15;
            break;
        case 'Z':
            Shoulder_z_pos-=0.15;
            break;
        case 'u':
            Upper_Arm_x_Angle+=1.0;
            break;
        case 'U':
            Upper_Arm_x_Angle-=1.0;
            break;
        case 'v':
            Upper_Arm_y_Angle+=1.0;
            break;
        case 'V':
            Upper_Arm_y_Angle-=1.0;
            break;
        case 'w':
            Upper_Arm_z_Angle+=1.0;
            break;
        case 'W':
            Upper_Arm_z_Angle-=1.0;
            break;
        case 'c':
            Forearm_x_Angle+=1.0;
            break;
        case 'C':
            Forearm_x_Angle-=1.0;
            break;
        case 'r':
            Forearm_z_Angle+=1.0;
            break;
        case 'R':
            Forearm_z_Angle-=1.0;
            break;
        case 'p':
            Hand_x_Angle+=1.0;
            break;
        case 'P':
            Hand_x_Angle-=1.0;
            break;
        case 'a':
            Hand_y_Angle+=1.0;
            break;
        case 'A':
            Hand_y_Angle-=1.0;
            break;
        case 'o':
            updatePerspective(GL_TRUE);
            break;
    }
    glutPostRedisplay();
}

void updatePerspective(GLboolean toggle)
{
    static GLboolean s_usePerspective = GL_TRUE;
    if (toggle)
        s_usePerspective = !s_usePerspective;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (s_usePerspective)
    {
        gluPerspective(50,1,1.0,1000.0);
    }
    else
    {
        glOrtho(-50.0, 50.0, -50.0, 50.0, 1, 1000);
    }
    glMatrixMode(GL_MODELVIEW);
}