#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "bicycle_class.hpp"


GLuint frame1;
GLuint pedals;
bic_node* bic_frame = new bic_node (NULL, frame1);
bic_node* bic_pedals = new bic_node(bic_frame, pedals);
int win_width = 640;
int win_height = 480;

void struct_frame();
void struct_pedals();
void tri(float, float, float);
void bicycle_frame();
void init_structures();

void init_structures()
{
    struct_frame();
    struct_pedals();
    bic_frame->set_glist(frame1);
    bic_pedals->set_glist(pedals);
    bic_pedals->change_params(1.5f, 0,-0.5f,0,0,0);
    bic_frame->add_child(bic_pedals);
}

void struct_frame()
{
    frame1 = glGenLists(1);
    glNewList(frame1, GL_COMPILE);
    tri(0.0f,1.0f,1.0f);
    glEndList();
}

void struct_pedals()
{
    pedals = glGenLists(1);
    glNewList(pedals, GL_COMPILE);
    tri(0.0f,0.0f,1.0f);
    glEndList();
}



void bicycle_frame()
{

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
    bic_frame->render_tree();
}