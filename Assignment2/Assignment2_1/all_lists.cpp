#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "bicycle_class.hpp"

/*
 * void gluCylinder(	GLUquadric*  	quad,
 	GLdouble  	base,
 	GLdouble  	top,
 	GLdouble  	height,
 	GLint  	slices,
 	GLint  	stacks);
 */

GLuint frame1;
GLuint frame2;
GLuint pedals;
bic_node* bic_frame_main = new bic_node ();
bic_node* bic_frame1 = new bic_node(bic_frame_main, frame1);
bic_node* bic_frame2 = new bic_node(bic_frame_main, frame2);
bic_node* bic_pedals = new bic_node(bic_frame_main, pedals);

int win_width = 640;
int win_height = 480;

void struct_frame();
void struct_frame1();
void struct_frame2();
void struct_pedals();
void tri(float, float, float);
void horizontal_cylinder(float);
void bicycle_frame();
void init_structures();

float len_frame1 = 5.601f;
float len_frame2 = 2.52f;
float len_frame3 = 4.818f;
float horizontal_tilt_frame1 = 16.17f;
float angle_frame2_1 = 85.0f;

void init_structures()
{
    struct_frame();
    struct_pedals();
    bic_frame1->set_glist(frame1);
    bic_frame1->change_params(0,0,0,0,0,-horizontal_tilt_frame1);
//    bic_pedals->set_glist(pedals);
//    bic_pedals->change_params(1.5f, 0,-0.5f,0,0,0);
    bic_frame_main->add_child(bic_frame1);
    bic_frame_main->add_child(bic_frame2);
}

void struct_frame()
{
    struct_frame1();
    struct_frame2();
}

void struct_frame1()
{
    frame1 = glGenLists(1);
    glNewList(frame1, GL_COMPILE);
    horizontal_cylinder(len_frame1);
    glPushMatrix();
    glTranslatef(-len_frame1/2,0,0);
    glRotatef(angle_frame2_1,0,0,1.0f);
    horizontal_cylinder(len_frame2);
    glPopMatrix();
    glTranslatef(len_frame1/2,0,0);
    glRotatef(90.0f,0,0,1.0f);
    horizontal_cylinder(len_frame3);
    glEndList();
}
void struct_frame2()
{
    frame2 = glGenLists(1);
    glNewList(frame2,GL_COMPILE);
    horizontal_cylinder(len_frame2);
    glEndList();
}
void struct_pedals()
{
    pedals = glGenLists(1);
    glNewList(pedals, GL_COMPILE);
    glEndList();
}

void horizontal_cylinder(float len_cylinder)
{
    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    GLUquadricObj *f1;
    f1 = gluNewQuadric();
    glTranslatef(-len_cylinder/2,0.0f,0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(f1,0.1f,0.1f,len_cylinder,32,32);
    glPopMatrix();
}

void bicycle_frame()
{
    horizontal_cylinder(5.601f);
}

void tri(float r, float g, float b)
{
    glBegin(GL_POLYGON);				// start drawing a polygon
    glColor3f(r,g,b);
    glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();
}

void draw_cycle()
{
    bic_frame_main->render_tree();
}