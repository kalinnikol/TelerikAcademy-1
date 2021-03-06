

#include <cstdlib>
#include <math.h>
#include <time.h>
#include <GL/glfw.h>
#include "okglib.h"
using namespace std;

float a;

int x = 332;
int y = 437;

int xpos = 0;
int ypos = 0;

int n = 4;

void GLFWCALL onMouseButton( int button, int action )
{
    if( button==GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        a += M_PI*2/48;
                if(a > M_PI*2)
        {
            a -= M_PI*2;
        }
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        a -= M_PI*2/48;
                        if(a < 0)
        {
            a += M_PI*2;
        }
    }
}



void drawSlider(float r,int count)
{
    glPushMatrix();
    glColor3ub(0,0,0);
    float alpha = a + M_PI*2/48/2;
    float dalpha = M_PI*2/count;
    glLineWidth(3);
    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBegin(GL_POINTS);
        glVertex3f(0,0,0);
    glEnd();
    glDisable(GL_POINT_SMOOTH);
    for(int i=0;i<count;i++)
    {
        drawCircleXY(r*cos(alpha),r*sin(alpha),0,0.5);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f((r-0.5)*cos(alpha),(r-0.5)*sin(alpha), 0);
        glEnd();
        alpha += dalpha;
        if(alpha > M_PI*2)
        {
            alpha = alpha - M_PI*2;
        }
    }
    glPopMatrix();
}


void GLFWCALL onKey( int key, int action )
{
    if( action==GLFW_PRESS )
    {
        switch(key)
        {
            case GLFW_KEY_UP:    if(n < 4) n++; break;
            case GLFW_KEY_DOWN:  if(n > 1) n--; break;

        }
    }
}

void drawColorCircle()
{
    float alpha= 0;
        float dalpha = M_PI*2/48;
        float r = 15;
        float component = 255;

        for(int i = 0; i < 16;i++)
        {
                glBegin(GL_TRIANGLES);
                    glColor3ub((255 - component), 0, component);
                    glVertex3f(r*cos(alpha), r*sin(alpha),0);
                    glVertex3f(r*cos(alpha + dalpha), r*sin(alpha + dalpha),0);
                    glVertex3f(0,0,0);
                glEnd();
                alpha += dalpha;
                if(alpha > M_PI*2)
                {
                    alpha = alpha - M_PI*2;
                }
                component -= 16;
                if(component <= 0)
                {
                    component = 0;
                }
        }

        component = 255;
        for(int i = 0; i < 16;i++)
        {
                glBegin(GL_TRIANGLES);
                    glColor3ub(255, (255-component), 0);
                    glVertex3f(r*cos(alpha), r*sin(alpha),0);
                    glVertex3f(r*cos(alpha + dalpha), r*sin(alpha + dalpha), 0);
                    glVertex3f(0,0,0);
                glEnd();
                alpha += dalpha;
                if(alpha > M_PI*2)
                {
                    alpha = alpha - M_PI*2;
                }
                component -= 16;
                if(component <= 0)
                {
                    component = 0;
                }
        }

        component = 255;
        for(int i = 0; i < 8;i++)
        {
                glBegin(GL_TRIANGLES);
                    glColor3ub((component), 255, 0);
                    glVertex3f(r*cos(alpha), r*sin(alpha), 0);
                    glVertex3f(r*cos(alpha + dalpha), r*sin(alpha + dalpha), 0);
                    glVertex3f(0,0,0);
                glEnd();
                alpha += dalpha;
                if(alpha > M_PI*2)
                {
                    alpha = alpha - M_PI*2;
                }
                component -= 32;
                if(component <= 0)
                {
                    component = 0;
                }
        }

        component = 255;
        for(int i = 0; i < 8;i++)
        {
                glBegin(GL_TRIANGLES);
                    glColor3ub(0, component, (255 - component));
                    glVertex3f(r*cos(alpha), r*sin(alpha), 0);
                    glVertex3f(r*cos(alpha + dalpha), r*sin(alpha + dalpha), 0);
                    glVertex3f(0,0,0);
                glEnd();
                alpha += dalpha;
                if(alpha > M_PI*2)
                {
                    alpha = alpha - M_PI*2;
                }
                component -= 32;
                if(component <= 0)
                {
                    component = 0;
                }
        }
}


void drawTable(float r, int count)
{
    float alpha = a + M_PI*2/48/2;
    float koef = M_PI*2/48;
    float dalpha = M_PI*2/count;

    int k = r;
    for(int i=0;i<count;i++)
    {
        if(alpha > 0 && alpha < M_PI*2/3)
        {
            glColor3ub(255 - (255 - 16*(alpha/koef)), 0, (255 - 16*(alpha/koef)));
        }
        else if(alpha > M_PI*2/3 && alpha < M_PI*4/3)
        {
            glColor3ub(255, (255-(255 - 16*alpha/koef)), 0);
        }
        else if(alpha > M_PI*4/3 && alpha < M_PI*5/3)
        {
            glColor3ub((255 - 32*alpha/koef), 255, 0);
        }
        else
        {
            glColor3ub(0, (255 - 32*alpha/koef), (255 - (255 - 32*alpha/koef)));
        }
        glBegin(GL_POLYGON);
            glVertex3f(-k-4 + i*2,-k-3,0);
            glVertex3f(-k-4 + i*2,-k-13,0);
            glVertex3f(-k-6 + i*2,-k-13,0);
            glVertex3f(-k-6 + i*2,-k-3,0);
        glEnd();
        alpha += dalpha;
        if(alpha > M_PI*2)
        {
            alpha = alpha - M_PI*2;
        }
    }
}

int main()
{
    init();

    glfwSetMouseButtonCallback( onMouseButton );
    glfwSetKeyCallback( onKey );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_NORMALIZE );
    glEnable( GL_DEPTH_TEST );


    glClearColor( 0,0,0,1 );

    a = 0;

    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );

        glLoadIdentity();
                gluLookAt(2.0f, 0.0f, 30.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f );

        drawSlider(14.25,n);
        drawColorCircle();

        drawTable(14.25,n);

        glfwSwapBuffers();
    }

    finit();
    return 0;
}

