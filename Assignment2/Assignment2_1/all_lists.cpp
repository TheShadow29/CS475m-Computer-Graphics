#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLuint frame1;
void struct_frame();
void tri();

void struct_frame()
{
    frame1 = glGenLists(2);
    glNewList(frame1, GL_COMPILE);
    tri();
    glEndList();
}


void tri()
{
    glBegin(GL_POLYGON);				// start drawing a polygon
    glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();
}

void draw_cycle()
{
    glPushMatrix();
    glCallList(frame1);
    glPopMatrix();
}