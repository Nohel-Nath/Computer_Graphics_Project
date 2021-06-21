#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#define PI 3.1416
unsigned int ID[35];
int floor1=0, road =1,tree=2,building=3,office=4,office1=1,office2=6,water=7,met=8,board=9,steel=10,build=11,mall1=12,res=13,mall2=14,school=15,center=16,football=17,sch=18,sch1=19,normal=20,roof=21,t=22,t1=23,t2=24,just=25,roof1=26,roof2=27,eye=28,sky=29,night=30,sun=31,moon=32,tire=33;
GLfloat alpha = 0.0, theta = 0.0,theta1 =0.0, axis_x=0.0, axis_y=0.0;
int timee=0;
GLboolean bRotate = false, uRotate = false;
float rot = 1;
float rotFan = 0;
bool flagrotate =true;
float Txval=0,Tyval=0,Tzval=0;
const int width = 1200;
const int height =1200;
int i =0;
float carz =17.5;
float carz1 = 17.5;
float huz=0;
float huz1=0;
bool l_on1 = true;
bool l_on2 = true;
bool l_on3 = true;
bool l_on4 = false;
bool sky_rotation =TRUE;

GLfloat eyeX = 0;
GLfloat eyeY = 6;
GLfloat eyeZ = 15;
GLfloat lookX = 0;
GLfloat lookY = 7;
GLfloat lookZ = 0;


static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {3,1,5,7},  //front
    {6,4,0,2},  //back
    {2,3,7,6},  //top
    {1,0,4,5},  //bottom
    {7,5,4,6},  //right
    {2,0,1,3}   //left
};
static GLfloat colors[1][3] =
{
    {0.0, 1.0, 1.0}

};


static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(float R=0.5, float G=0.5, float B=0.5, int type=0, float val=1)
{

    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {30};

    GLfloat m_em[] = {1,1,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);



    if(!l_on1)


        glMaterialfv(GL_FRONT, GL_EMISSION, m_no);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);
        glTexCoord2f(val,0);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(val,val);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(0,val);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
    }
    glEnd();
}

float l_height=10;
float val =0;
void light1(float a,float b,float c)
{
    glEnable(GL_LIGHT0);

    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1-val, 1-val, 1-val, 1.0};
    GLfloat l_dif[] = {1-val,1-val,1-val,1};
    GLfloat l_spec[] = {1-val,1-val,1-val,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on1)
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
    if(l_on1)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
    if(l_on1)
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);


}
void spot_light(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT1);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0, 0, 1, 1.0};
    GLfloat l_dif[] = {1,1,1,1};
    GLfloat l_spec[] = {1,1,1,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on2)
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
    if(l_on2)
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
    if(l_on2)
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT1, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {50};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);

}
void circle_3D(GLdouble radius)
{
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);

    glRotatef(270, 1, 0, 0);
    gluSphere(qobj, radius, 20, 20);
    gluDeleteQuadric(qobj);

}

void halfcircle(float radius_x, float radius_y)
{
    int i = 0;
    float angle1 = 0.0;

    glBegin(GL_POLYGON);

    for(i = 0; i < 51; i++)
    {
        angle1 = 2 * PI * i / 100;
        glVertex3f (cos(angle1) * radius_x, sin(angle1) * radius_y, 0);
    }

    glEnd();
}


void road1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[roof]);
    glPushMatrix();
    glScalef(7,.3,21);
    glTranslatef(-0.5,.8,-0.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, ID[road]);
    glPushMatrix();
    glScalef(.2,.3,20);
    glTranslatef(-16,.85,-0.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,.3,20);
    glTranslatef(15,.85,-0.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,.3,3);
    glTranslatef(-.5,.85,-1);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,.3,3);
    glTranslatef(-.5,.85,-3);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,.3,3);
    glTranslatef(-.5,.85,1);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,.3,3);
    glTranslatef(-.5,.85,2.3);
    cube(1,1,1);
    glPopMatrix();


    // glDisable(GL_TEXTURE_2D);


}

void wall()
{
    //floor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[floor1]);
    glPushMatrix();
    glScalef(25,1,21);
    glTranslatef(-0.5,-.5,-0.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void Tree()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[tree]);

    glPushMatrix();//tree1
    glTranslatef(-12,.5,-9.5);
    glScalef(.5,4,.5);
    cube(0.55,0.27,0.0745);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.8,4,-10.5);
    glScalef(2,1.5,2);
    cube(0,.9,0);
    glPopMatrix();

    glPushMatrix();//tree2
    glTranslatef(-8.5,.5,-9.5);
    glScalef(.5,4,.5);
    cube(0.55,0.27,0.0745);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.4,4,-10.5);
    glScalef(2,1.5,2);
    cube(0,.9,0);
    glPopMatrix();

    glPushMatrix();//tree3
    glTranslatef(-5,.5,-9.5);
    glScalef(.5,4,.5);
    cube(0.55,0.27,0.0745);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.7,4,-10.5);
    glScalef(2,1.5,2);
    cube(0,.9,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void brench()
{
    glPushMatrix();
    glTranslatef(-10,.4,-4.5);
    glScalef(.5,.7,.5);
    cube(.2,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,.4,-6.5);
    glScalef(.5,.7,.5);
    cube(.2,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,.4,-6.5);
    glScalef(.5,.7,.5);
    cube(.2,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,.4,-4.5);
    glScalef(.5,.7,.5);
    cube(.2,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.5,1,-7);
    glScalef(5,.5,3.5);
    cube(0.647, 0.165, 0.165);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.5,1,-6.7);
    glScalef(5,1.5,.5);
    cube(0.502, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.5,4,-7);
    glScalef(.5,.5,5.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.5,.5,-6.5);
    glScalef(.3,1.5,.3);
    cube(0.55,0.27,0.0745);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.5,.5,-2.5);
    glScalef(.3,3.5,.3);
    cube(0.55,0.27,0.0745);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.5,1.5,-3.5);
    glScalef(.3,2.5,.3);
    cube(0.55,0.27,0.0745);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.5,1.5,-5.5);
    glScalef(.3,2.5,.3);
    cube(0.55,0.27,0.0745);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.3,1.3,-5.9);
    glScalef(1.5,.3,2.5);
    cube(0.55, 0.27, .0745);
    glEnd();
    glPopMatrix();
}

void Building()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[building]);
    glPushMatrix();
    glTranslatef(5,.7,-3);
    glScalef(1.5,6.5,2.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5,.7,-3);
    glScalef(1.5,5,2.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,.7,-3);
    glScalef(1.5,6.5,2.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,.7,1);
    glScalef(1.5,5,2.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5,.7,1);
    glScalef(1.5,6.5,2.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,.7,1);
    glScalef(1.5,5,2.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[roof1]);
    glPushMatrix();
    glTranslatef(7.5,7.2,1);
    glScalef(1.5,.2,2.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,7.2,-3);
    glScalef(1.5,.2,2.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10,7.2,-3);
    glScalef(1.5,.2,2.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.5,5.7,-3);
    glScalef(1.5,.2,2.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10,5.7,1);
    glScalef(1.5,.2,2.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,5.7,1);
    glScalef(1.5,.2,2.5);
    cube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}
void Office()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[office]);
    glPushMatrix();
    glTranslatef(8.3,.5,4);
    glScalef(.9,3.5,1);
    cube(.53,.8,.98);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(8.4,4,4);
    glScalef(.7,.1,1);
    cube(1,1,1);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[office]);
    glPushMatrix();
    glTranslatef(8.4,4.1,4);
    glScalef(.7,2.5,1);
    cube(.53,.8,.98);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(8.5,6.6,4);
    glScalef(.5,.1,1);
    cube(1,1,1);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[office]);
    glPushMatrix();
    glTranslatef(8.5,6.7,4);
    glScalef(.5,1.5,1);
    cube(.53,.8,.98);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(8.7,8.3,4.6);
    glScalef(.1,1.5,.1);
    cube(1,1,1);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[office1]);
    glPushMatrix();
    glTranslatef(5,.5,4);
    glScalef(1.5,5.5,1.5);
    cube(.53,.8,.98);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[office1]);
    glPushMatrix();
    glTranslatef(10.5,.5,4);
    glScalef(1.5,5.5,1.5);
    cube(.53,.8,.98);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[roof2]);
    glPushMatrix();
    glTranslatef(10.5,6,4);
    glScalef(1.5,.15,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,6,4);
    glScalef(1.5,.15,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.5,6.7,9.3);
    glScalef(5.5,.15,.8);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void playground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[football]);

    glPushMatrix();
    glTranslatef(5,.5,-9.5);
    glScalef(6.5,.2,6);
    cube(0,.9,0);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void swimmingpool()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[water]);

    glPushMatrix();
    glTranslatef(8.3,.5,6.3);
    glScalef(2.6,1,2);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[met]);
    glPushMatrix();
    glTranslatef(8,.5,5.8);
    glScalef(3,1.2,.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,.5,8.3);
    glScalef(3,1.2,.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.7,.5,5.8);
    glScalef(.5,1.2,3);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.5,.5,5.8);
    glScalef(.5,1.2,3);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[build]);
    glPushMatrix();
    glTranslatef(5.5,.7,9.3);
    glScalef(5.5,6,.8);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void Board()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[board]);
    glPushMatrix();
    glTranslatef(5.7,2.2,6);
    glScalef(.5,2,2.5);
    cube(1,1,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[steel]);
    glPushMatrix();
    glTranslatef(5.7,.5,7.2);
    glScalef(.2,1.7,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void shoppingmall()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[res]);
    glPushMatrix();
    glTranslatef(-11.5,.7,-1.8);
    glScalef(2.8,2.6,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.5,3.3,-1.8);
    glScalef(2.8,2.6,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5,.7,-1.8);
    glScalef(2.8,2.6,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,3.3,-1.8);
    glScalef(2.8,2.6,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[mall1]);
    glPushMatrix();
    glTranslatef(-7.5,.7,.5);
    glScalef(2.8,3,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,.7,2.5);
    glScalef(2.8,3,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[mall2]);
    glPushMatrix();
    glTranslatef(-11.5,.7,.5);
    glScalef(2.8,3,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.5,.7,2.5);
    glScalef(2.8,3,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[school]);
    glPushMatrix();
    glTranslatef(-11.5,.7,4.5);
    glScalef(2,1.5,.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[sch]);
    glPushMatrix();
    glTranslatef(-11.7,.7,5);
    glScalef(.5,1.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[sch1]);
    glPushMatrix();
    glTranslatef(-11.5,.7,6.5);
    glScalef(2,1.5,.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[normal]);
    glPushMatrix();
    glTranslatef(-7.7,.7,5);
    glScalef(2.3,1.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[center]);
    glPushMatrix();
    glTranslatef(-7.7,.7,7);
    glScalef(2.3,2.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[t1]);
    glPushMatrix();
    glTranslatef(-11.8,.5,7.2);
    glScalef(3,.05,2.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[t2]);
    glPushMatrix();
    glTranslatef(-7.7,.7,9);
    glScalef(2.3,1.5,.7);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[just]);
    glPushMatrix();
    glTranslatef(-11.5,5.8,-1.8);
    glScalef(2.8,.2,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.5,5.8,-1.8);
    glScalef(2.8,.2,1.5);
    cube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-7.5,3.7,.5);
    glScalef(2.8,.2,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5,3.7,2.5);
    glScalef(2.8,.2,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.5,3.7,.5);
    glScalef(2.8,.2,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.5,3.7,2.5);
    glScalef(2.8,.2,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.55,.4,2.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.7,.4,2.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.7,.4,2.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.55,.4,2.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.7,.4,.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.55,.4,.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.55,.4,.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.7,.4,.5);
    glScalef(.05,3.5,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.7,.6,-1.8);
    glScalef(.05,5.4,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.7,.6,-1.8);
    glScalef(.05,5.4,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-11.55,.6,-1.8);
    glScalef(.05,5.4,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.55,.6,-1.8);
    glScalef(.05,5.4,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[t]);
    glPushMatrix();
    glTranslatef(-7.7,2.2,5);
    glScalef(2.3,.2,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.5,2.2,4.5);
    glScalef(2,.2,.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.5,2.2,6.5);
    glScalef(2,.05,.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.7,2.2,5);
    glScalef(.5,.05,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.7,3.2,7);
    glScalef(2.3,.1,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.7,2.2,9);
    glScalef(2.3,.1,.7);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5.41,.7,9);
    glScalef(.05,1.6,.7);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.75,.7,9);
    glScalef(.05,1.6,.7);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5.4,.3,7);
    glScalef(.05,3,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.75,.3,7);
    glScalef(.05,3,1.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.4,.3,5);
    glScalef(.05,1.9,1.5);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7.75,.3,5);
    glScalef(.05,1.9,1.5);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void lampost()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[steel]);
    glPushMatrix();
    glTranslatef(-3.2,.5,7.2);
    glScalef(.2,5,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.2,.5,2.2);
    glScalef(.2,5,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.2,.5,-4.2);
    glScalef(.2,5,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,5,7.2);
    glScalef(2,.2,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,5,2.2);
    glScalef(2,.2,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,5,-4.2);
    glScalef(2,.2,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.2,4,7.2);
    glScalef(.2,1,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.2,4,2.2);
    glScalef(.2,1,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.2,4,-4.2);
    glScalef(.2,1,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-2.1,3.7,7.2);
    glColor3f(1,1,1);
    glutSolidSphere(.4,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.1,3.7,2.2);
    glColor3f(1,1,1);
    glutSolidSphere(.4,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.1,3.7,-4.2);
    glColor3f(1,1,1);
    glutSolidSphere(.4,10,10);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[steel]);
    glPushMatrix();
    glTranslatef(3,.5,7.2);
    glScalef(.2,5,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,.5,2.2);
    glScalef(.2,5,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,.5,-4.2);
    glScalef(.2,5,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,5,7.2);
    glScalef(2,.2,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,5,2.2);
    glScalef(2,.2,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,5,-4.2);
    glScalef(2,.2,.2);
    cube(.8,.8,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,4,7.2);
    glScalef(.2,1,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2,4,2.2);
    glScalef(.2,1,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2,4,-4.2);
    glScalef(.2,1,.2);
    cube(.8,.8,.8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(2.1,3.7,7.2);
    glColor3f(1,1,1);
    glutSolidSphere(.4,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,3.7,2.2);
    glColor3f(1,1,1);
    glutSolidSphere(.4,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,3.7,-4.2);
    glColor3f(1,1,1);
    glutSolidSphere(.4,10,10);
    glPopMatrix();
}

void spot()
{
    glPushMatrix();
    glTranslatef(2,4,-4);
    spot_light(1,1,1);
    glPopMatrix();
}

void human()
{
    glPushMatrix();
    glTranslatef(-3.9,3.2,-70.2);
    glColor3f(1.000, 0.855, 0.725);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,2.7,-70.3);
    glScalef(.2,.3,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.2,2.1,-70.5);
    glScalef(.6,.7,.6);
    cube(0.698, 0.133, 0.133);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4.2,1.3,-70.5);
    glScalef(.6,.8,.6);
    cube(.416, 0.353, 0.804);
    glPopMatrix();
//leg
    glPushMatrix();
    glTranslatef(-4.1,.7,-70.3);
    glScalef(.1,.9,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.9,.7,-70.3);
    glScalef(.1,.9,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.9,.5,-70.3);
    glScalef(.1,.2,.3);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.1,.5,-70.3);
    glScalef(.1,.2,.3);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

//hand
    glPushMatrix();
    glTranslatef(-4.4,2.6,-70.3);
    glScalef(.4,.1,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.8,2.6,-70.3);
    glScalef(.4,.1,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,1.9,-70.3);
    glScalef(.1,.8,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.4,1.9,-70.3);
    glScalef(.1,.8,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    //eye
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[eye]);
    glPushMatrix();
    glTranslatef(-4,3.3,-69.9);
    glColor3f(0, 0, 0);
    glutSolidSphere(.06,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.8,3.3,-69.9);
    glColor3f(0, 0, 0);
    glutSolidSphere(.06,10,10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
void human1()
{
    glPushMatrix();
    glTranslatef(4.1,3.2,7.2);
    glColor3f(1.000, 0.855, 0.725);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,2.7,7.1);
    glScalef(.2,.3,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.8,2.1,6.9);
    glScalef(.6,.7,.6);
    cube(0.698, 0.133, 0.133);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.8,1.3,6.9);
    glScalef(.6,.8,.6);
    cube(.416, 0.353, 0.804);
    glPopMatrix();
//leg
    glPushMatrix();
    glTranslatef(4.1,.7,7.1);
    glScalef(.1,.9,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.9,.7,7.1);
    glScalef(.1,.9,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.9,.5,7);
    glScalef(.1,.2,.3);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.1,.5,7);
    glScalef(.1,.2,.3);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

//hand
    glPushMatrix();
    glTranslatef(4.3,2.6,7.1);
    glScalef(.4,.1,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5,2.6,7.1);
    glScalef(.4,.1,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5,1.9,7.1);
    glScalef(.1,.8,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.6,1.9,7.1);
    glScalef(.1,.8,.2);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    //eye
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[eye]);
    glPushMatrix();
    glTranslatef(4.2,3.3,6.9);
    glColor3f(0, 0, 0);
    glutSolidSphere(.06,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,3.3,6.9);
    glColor3f(0, 0, 0);
    glutSolidSphere(.06,10,10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
void human_animation()
{

    if(huz<=102)
    {

        huz +=.005;
    }
    if(huz>=102)
    {
        huz = 20;

    }
    //glTranslatef(0,0,2);
    glutPostRedisplay();

}
void human1_animation()
{

    if(huz1<=102)
    {

        huz1 +=.005;
    }
    if(huz1>=102)
    {
        huz1 = -5;

    }
    //glTranslatef(0,0,2);
    glutPostRedisplay();

}


void human_move()
{

    for(int i=1; i<=60; i+=4)
    {
        glPushMatrix();
        glTranslatef(0,0, - i + huz);
        human();
        human_animation();
        glPopMatrix();
    }
}

void human1_move()
{

    for(int i=1; i<=60; i+=4)
    {
        glPushMatrix();
        glTranslatef(0,0, - i - huz1);
        human1();
        human1_animation();
        glPopMatrix();
    }
}


void cars()
{
    glPushMatrix();
    glTranslatef(.4,1,3.1);
    glScalef(2.3,1.3,4);
    cube(.5,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.4,2.3,4);
    glScalef(2.3,.6,2.4);
    cube(0,0,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7,1.5,7);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7,1.5,3);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,1.5,3);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,1.5,7);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[tire]);
    glPushMatrix();
    glTranslatef(2.2,.9,6.5);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.8,.9,6.5);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.8,.9,4);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.2,.9,4);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void cars1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[tire]);
    glPushMatrix();
    glTranslatef(-2.3,.9,-80.5);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.8,.9,-80.5);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.8,.9,-78);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.3,.9,-78);
    glColor3f(0,0,0);
    glutSolidSphere(.3,10,10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-2.7,1,-81.1);
    glScalef(2.3,1.3,4);
    cube(.5,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.7,2.3,-80.3);
    glScalef(2.3,.6,2.4);
    cube(0,0,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.3,1.5,-77);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2,1.5,-77);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2,1.5,-81.3);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.3,1.5,-81.3);
    glScalef(.5,.5,.2);
    cube(1,1,1);
    glPopMatrix();

}

void car_animation()
{

    if(carz<=102)
    {

        carz +=.04;
    }
    if(carz>=102)
    {
        carz = 14;

    }
    //glTranslatef(0,0,2);
    glutPostRedisplay();

}

void car_animation1()
{

    if(carz1<=102)
    {

        carz1 +=.04;
    }
    if(carz1>=102)
    {
        carz1 = 1;

    }

    glutPostRedisplay();
}
void car_move()
{

    for(int i=1; i<=30; i+=10)
    {
        glPushMatrix();
        glTranslatef(0,0, - carz + i);
        cars();
        car_animation();
        glPopMatrix();
    }

}
void car_move1()
{

    for(int i=1; i<=30; i+=10)
    {
        glPushMatrix();
        glTranslatef(0,0, -i + carz1);
        cars1();
        car_animation1();
        glPopMatrix();
    }

}
bool nohel= 0;
void Sun()
{
    timee++;
    printf("%d \n",timee);
    if(timee<500 )
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID[sun]);
        glPushMatrix();
        glTranslatef(1,45,-80);
        glColor3f(1,1,1);
        val=.6;
        glutSolidSphere(3.5,9,9);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        val=0;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID[moon]);
        glPushMatrix();
        if(!nohel)
        {
            l_on1 = 0;
            nohel=1;

        }

        glTranslatef(1,25,-25);
        glColor3f(1,1,1);
        glutSolidSphere(2,9,9);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        if(timee>2000 )
        {

            timee=0;
            nohel=0;
        }
    }

}
void Sky()
{
    glRotatef(theta1, 0,1,0);
    glPushMatrix();
    circle_3D(100);
    glPopMatrix();

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    glViewport(0, 0, width, height);

    glRotatef(rot, 0.0, 1, 0.0 );
    for (int i=0; i<=100; i= i+21)
    {
        glPushMatrix();
        glTranslatef(0,0,-i);
        wall();
        road1();
        Tree();
        brench();
        Building();
        Office();
        swimmingpool();
        shoppingmall();
        playground();
        lampost();
        glPopMatrix();
    }
    Board();
    car_move();
    car_move1();
    human_move();
    human1_move();
    spot();
    Sun();
    if(timee<500)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID[sky]);
        glPushMatrix();
        Sky();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID[night]);
        glPushMatrix();
        Sky();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        if(timee>2000)
        {
            timee=0;
        }
    }
    light1(10,10,10);
    glFlush();
    glutSwapBuffers();
}

static void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    // Rotation
    case 'b':
        rot++;
        break;
    case 'c':
        rot--;
        break;

    // Zoom
    case '1':
        eyeZ++;
        lookZ++;
        break;
    case '2':
        eyeZ--;
        lookZ--;
        break;

    case '3':
        eyeX++;
        lookX++;
        break;
    case '4':
        eyeX--;
        lookX--;
        break;

    case '7':
        l_on1=1-l_on1;
        break;
    case '8':
        l_on2=1-l_on2;
        break;
    case '9':
        l_on1=1-l_on1;
        break;
    case '5':
        eyeY++;
        lookY++;
        break;
    case '6':
        eyeY--;
        lookY--;
        break;
    case 'm':
        eyeZ=-70;
        eyeY=70;

        break;
    case 'n':
        eyeZ++;
        break;

    case '0':
        //
        break;

    }

    glutPostRedisplay();
}


static void idle(void)
{

    glutPostRedisplay();
}
void animate()
{
    if (flagrotate == true)
    {
        rotFan+= 0.2;

    }
    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);


    }
    if (sky_rotation)
    {
        theta1 += .5;
        if( theta1>360  )
        {
            theta1=0;

        }

    }
    glutPostRedisplay();
}

void LoadTexture(const char*filename, int index)
{
    glGenTextures(1, &ID[index]);
    glBindTexture(GL_TEXTURE_2D, ID[index]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void texture()
{
    LoadTexture("D:\\Nohel\\Main project\\Texture image\\floor.bmp", floor1);
    LoadTexture("D:\\Nohel\\Main project\\Texture image\\road3.bmp", road);
    LoadTexture("D:\\Nohel\\Main project\\Texture image\\tree2.bmp", tree);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\building1.bmp",building);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\glass.bmp",office);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\building.bmp",office1);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\water.bmp",water);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\me.bmp",met);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\start.bmp",board);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\steel.bmp",steel);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\build.bmp",build);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\res.bmp",res);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\school.bmp",school);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\texture.bmp",center);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\mall2.bmp",mall1);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\mall3.bmp",mall2);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\football.bmp",football);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\school(1).bmp",sch);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\school(2).bmp",sch1);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\normal.bmp",normal);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\rooftop.bmp",roof);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\just.bmp",just);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\tails.bmp",t);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\tennis.bmp",t1);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\gym.bmp",t2);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\roof.bmp",roof1);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\roof1.bmp",roof2);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\eye.bmp",eye);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\sky.bmp",sky);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\night.bmp",night);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\sun.bmp",sun);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\moon.bmp",moon);
    LoadTexture("D:\Nohel\\Main project\\Texture image\\tire.bmp",tire);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(height, width);
    glutCreateWindow("Project");

    texture();

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);



    glEnable(GL_LIGHTING);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);




    glutMainLoop();

    return 0;
}

