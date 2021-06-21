#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false,tv=false;
float rot = 0;
float rotFan = 0;
bool flagrotate =true;
float Txval=0,Tyval=0,Tzval=0;
const int width = 700;
const int height = 700;
int l_on =9;
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
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
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

void cube(float R=0.5, float G=0.5, float B=0.5, bool e=false, float alpha=1)
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

    if(e & l_on) glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
    else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}
float l_height=10;
void light()
{
    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat l_dif[] = {1,1,1,1};
    GLfloat l_spec[] = {1,1,1,1};
    GLfloat l_pos[] = {1,l_height,0,1.0};

    glEnable(GL_LIGHT0);

    if(l_on) glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
    else glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
    if(l_on) glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
    else glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
    if(l_on) glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
    else glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);

    // spot light extra
   // GLfloat l_spt[] = {0,-1,0,1};
   // GLfloat spt_ct[] = {spt_cutoff};
   //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l_spt);
   // glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spt_ct);
}

void wall()
{   //floor
    glPushMatrix();
    glScalef(16,1,20);
    glTranslatef(-0.5,-.5,-0.5);
    cube(1,1,1.0);
    glPopMatrix();
    //wall
    glPushMatrix();
    glScalef(16.0, 12.0, 1.0);
    glTranslatef(-0.5,0.0,-11);
    cube(0.9, 1, 0.7);
    glPopMatrix();
    //right
    glPushMatrix();
    glScalef(1.0, 12.0, 20.0);
    glTranslatef(8,0.0,-.5);
    cube(0.7, 0.7, 0.7);
    glPopMatrix();
    //left
    glPushMatrix();
    glScalef(1.0, 12.0, 20.0);
    glTranslatef(-9,0.0,-.5);
    cube(0.7, 0.7, 0.7);
    glPopMatrix();
    //top
    glPushMatrix();
    glScalef(18,1,20);
    glTranslatef(-.5,12,-0.5);
    cube(0.9,1,0.9);
    glPopMatrix();



}

void window1()
{
    glPushMatrix();
    glScalef(0.2, 2.5, 2.5);
    glTranslatef(-40,3,-1.5);
    cube(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.8,8.7,-3.7);
    glScalef(0.1, .1, 2.5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.8,7.5,-2.7);
    glScalef(0.05,2.5,0.1);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();
}

void window2()
{
    glPushMatrix();
    glScalef(0.2, 2.5, 2.5);
    glTranslatef(39,3,-1.5);
    cube(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.7,8.7,-3.7);
    glScalef(0.1, .1, 2.5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.7,7.5,-2.5);
    glScalef(0.05,2.5,0.1);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();


}

void tubelight()
{
    glPushMatrix();
    glScalef(0.2, .5, 2.5);
    glTranslatef(39.8,21.5,-3);
    glScalef(0.2, .5, 2.8);
    cube(1, 1, 1);
    glPopMatrix();
}

void bed()
{
    //khat
    glPushMatrix();
    glScalef(5.0, 1.8, 9.0);
    glTranslatef(-1,0.0,-1);
    cube(1, 0.1, .1);
    glPopMatrix();
    //chador
    glPushMatrix();
    glTranslatef(-.2, 0.2, -.3);
    glScalef(4.95, 1.8, 3.0);
    glTranslatef(-1,0.0,-1.0);
    cube(0.3, 0.1, 0.8);
    glPopMatrix();
    //chador
    glPushMatrix();
    glTranslatef(0.0, 0.2, -.3);
    glScalef(4.95, 1.8, 3.0);
    glTranslatef(-.97,0.0,-1.0);
    cube(0.3, 0.1, 0.8);
    glPopMatrix();
    //balis-1
    glPushMatrix();
    glTranslatef(-.5, 0.2, -6.8);
    glScalef(1.9, 1.8, 2);
    glTranslatef(-.9,0.0,-.1);
    cube(.9, 1, .1);
    glPopMatrix();
    //balis-2
    glPushMatrix();
    glTranslatef(-2.5, 0.2, -6.8);
    glScalef(1.9, 1.8, 2);
    glTranslatef(-1.2,0.0,-.1);
    cube(.9, 1, .1);
    glPopMatrix();
    //bed-wall
    glPushMatrix();
    glTranslatef(-.04,0,-.5);
    glScalef(5, 2.5, 0.5);
    glTranslatef(-1,.6,-17);
    cube(0.6, .1, 0.0);
    glPopMatrix();
}

void almari()
{
    glPushMatrix();
    glTranslatef(-8.5, 0, -4.5);
    glScalef(1.5, 7.3, 3);
    cube(0.6, .1, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 4.6, -3);
    glScalef(.05, 2.5, 1.3);
    cube(0.690, 0.878, 0.902);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 3.7, -3.5);
    glScalef(.2, .1, 1);
    cube(1, 1, 1);
    glPopMatrix();

}
void ac()
{
    glPushMatrix();
    glScalef(3, 1.85, 2);
    glTranslatef(-2.75,5.8,-2.5);
    glScalef(0.2, .5, 2.8);
    cube(0, 0, .6);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.25, 1.3, 1.5);
    glTranslatef(-30.5,8.3,-2.9);
    glScalef(0.2, .5, 2.8);
    cube(0, .5, 1);
    glPopMatrix();
}
void lampost()
{
    glPushMatrix();
    glScalef(1.5, 1, 1.5);
    glTranslatef(-4.7,0.0,-5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();
//stand
    glPushMatrix();
    glTranslatef(-6.5,1,-7);
    glScalef(.3,4.5,.3);
    cube(0.6, .1, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,5.55,-8);
    glScalef(1.5,1.5,2.5);
    cube(1,0,0);
    glPopMatrix();
}


void WAREDROBE()
{   //maindrove
    glPushMatrix();
    glTranslatef(-6, 0.9, 3.0);
    glScalef(3.0, 3.5, 3.0);
    glTranslatef(-0.5,0.0,-0.5);
    cube(0.6, .1, 0.0);
    glPopMatrix();
    //lowerdrawer
    glPushMatrix();
    glTranslatef(-4.6, 1.3, 3.0);
    glScalef(.5, .5, 2.5);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.45, 0.0, 0.0);
    glPopMatrix();
    //rightdrawer
    glPushMatrix();
    glTranslatef(-4.6, 2.2, 2.3);
    glScalef(.5, 2, 1.1);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.45, 0.0, 0.0);
    glPopMatrix();
    //leftdrawer
    glPushMatrix();
    glTranslatef(-4.6, 2.2, 3.2);
    glScalef(.5, 2, 1.1);
    glTranslatef(-0.5,0.0,.1);
    cube(.45, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3, 1.5, 2.9);
    glScalef(.1, .1, .3);
    glTranslatef(-0.5,0.0,.1);
    cube(1, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3, 2.8, 2.2);
    glScalef(.1, .6, .1);
    glTranslatef(-0.5,0.0,.1);
    cube(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3, 2.8, 3.8);
    glScalef(.1, .6, .1);
    glTranslatef(-0.5,0.0,.1);
    cube(1, 1, 1);
    glPopMatrix();

}
void wardrove1()
{
     //drove
    glPushMatrix();
    glTranslatef(6, 0.5,.5);
    glScalef(3.0, 3.8, 9.0);
    glTranslatef(-0.5,0.0,-0.5);
    cube(0.6, .1, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.4, 1, 3.5);
    glScalef(.2, 3.3, 1.8);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.45, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.4, 1, .8);
    glScalef(.2, 3.3, 1.8);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.45, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.4, 1, -2.2);
    glScalef(.2, 3.3, 1.8);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.45, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.3, 2.15, -2.2);
    glScalef(.2, .6, .2);
    glTranslatef(-0.5,0.0,-0.5);
    cube(1, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.3, 2.15, .8);
    glScalef(.2, .6, .2);
    glTranslatef(-0.5,0.0,-0.5);
    cube(1, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.3, 2.15, 3.5);
    glScalef(.2, .6, .2);
    glTranslatef(-0.5,0.0,-0.5);
    cube(1, 1.0, 1.0);
    glPopMatrix();





}
void lookinglass()
 {
     //drove
    glPushMatrix();
    glTranslatef(3.5, 0.9, -7.0);
    glScalef(4, 2.5, 2.5);
    glTranslatef(-0.5,0.0,-0.5);
    cube(0.6, .1, 0.0);
    glPopMatrix();
    //drawer
    glPushMatrix();
    glTranslatef(3.5, 1.2, -5.6);
    glScalef(3.5, 1.8, .4);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.45, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5, 1.8, -5.35);
    glScalef(.1, .6, .1);
    glTranslatef(-0.5,0.0,-0.5);
    cube(1, 1.0, 1.0);
    glPopMatrix();
    //glass
    glPushMatrix();
    glTranslatef(3.4, 3.5, -7.1);
    glScalef(3.2, 3.5, .1);
    glTranslatef(-0.5,0.0,-0.5);
    cube(0.690, 0.878, 0.902);
    glPopMatrix();





 }
void television()
{   //land
    glPushMatrix();
    glTranslatef(4.7, 2, 8.0);
    glScalef(4, .5, 3.2);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.3, 1, 1);
    glPopMatrix();
    //stand1
    glPushMatrix();
    glTranslatef(6.45,.1,8.6);
    glScalef(.3,2,.3);
    cube(0, 0, 0);
    glPopMatrix();
    //stand2
    glPushMatrix();
    glTranslatef(2.7,.1,8.6);
    glScalef(.3,2,.3);
    cube(0, 0, 0);
    glPopMatrix();
    //stand3
    glPushMatrix();
    glTranslatef(2.7,.1,7.1);
    glScalef(.3,2,.3);
    cube(0, 0, 0);
    glPopMatrix();
    //stand4
    glPushMatrix();
    glTranslatef(6.4,.1,7.1);
    glScalef(.3,2,.3);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.9, 2.5, 8.0);
    glScalef(1.3, 3.8, 2.6);
    glTranslatef(-0.5,0.0,-0.5);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.4, 2.8, 8.0);
    glScalef(.4, 3.2, 2);
    glTranslatef(-0.5,0.0,-0.5);
    cube(0.690, 0.878, 0.902,tv);
    glPopMatrix();

    //light();
}
void sofa()
{
    glPushMatrix();
    glTranslatef(-5, -.5, 7.5);
    glScalef(2.5, 2.8, 4);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.4, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.2, 2.3, 7.5);
    glScalef(.1, 3, 4);
    glTranslatef(-0.5,0.0,-0.5);
    cube(.5, .1, .1);
    glPopMatrix();
}

void fan()
{
    glPushMatrix();
    glTranslatef(0.0,8.2,-4.6);
    glScalef(0.2,4.0,0.2);
    cube(0.1, 0.2, 0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.2,7.5,-5);
    glScalef(.5,0.7,1.0);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(-3.7,7.7,-4.7);
    glScalef(3.5,0.3,.3);
    cube(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.3,7.7,-4.7);
    glScalef(3.5,0.3,.3);
    cube(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.1,7.5,-4);
    glScalef(.3,.3,3.5);
    cube(1, 1, 1);
    glPopMatrix();




}



void extra()
{
    glPushMatrix();
    glScalef(4.5, .3, 1.5);
    glTranslatef(1.57,5.8,-6.7);
    glScalef(0.2, .5, 2.8);
    cube(.3, .3, .3);
    glPopMatrix();

    glPushMatrix();
    glScalef(4.5, .3, 1.5);
    glTranslatef(1.57,13.5,-6.0);
    glScalef(0.2, .5, 2.8);
    cube(0.3, 0.3, 0.3);
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 3.2, .2);
    glTranslatef(3.77,.6,-37.3);
    glScalef(0.2, .5, 2.8);
    cube(0.5, .3, .5);
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 3.2, .2);
    glTranslatef(3.77,.6,-45.3);
    glScalef(0.2, .5, 2.8);
    cube(0.5, .5, .7);
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 3.2, .2);
    glTranslatef(3.77,1.25,-30.3);
    glScalef(0.2, .5, 2.8);
    cube(0.7, .2, .3);
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 3.2, .2);
    glTranslatef(3.77,1.25,-40.3);
    glScalef(0.2, .5, 2.8);
    cube(0.4, 0, .1);
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

    wall();
    window1();
    window2();
    tubelight();
    bed();
    almari();
    lampost();
    ac();
    lookinglass();
    extra();
    television();
    sofa();
    fan();
    WAREDROBE();
    wardrove1();
    light();
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
        l_height--;
        break;
    case '8':
        l_height++;
        break;

    case '5':
        eyeY++;
        lookY++;
        break;
    case '6':
        eyeY--;
        lookY--;
        break;

        case '0':
            tv=!tv;

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
    glutPostRedisplay();
}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(height, width);
    glutCreateWindow("Bedroon");
    glEnable(GL_LIGHTING);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
