#include <cmath>
#include <math.h>
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

#define PI 3.14159265

GLuint frame1;
GLuint frame2;
GLuint frame3;
GLuint frame4;
GLuint fwp1;
GLuint wheel1;
GLuint pedals;
GLuint spoke1;
GLuint pedal_rod1;
GLuint wheel_axle1;

const int num_spokes = 12;

bic_node* bic_frame_main = new bic_node ();
bic_node* bic_frame1 = new bic_node(bic_frame_main, frame1);
bic_node* bic_frame2 = new bic_node(bic_frame1, frame2);
bic_node* bic_frame3 = new bic_node(bic_frame1,frame3);
bic_node* bic_frame4 = new bic_node(bic_frame1,frame4);
bic_node* bic_front_wheel_pad = new bic_node(bic_frame1,fwp1);
bic_node* bic_front_wheel = new bic_node(bic_front_wheel_pad,wheel1);
bic_node* bic_front_wheel_axel = new bic_node(bic_front_wheel,wheel_axle1);
bic_node* bic_pedal_rod = new bic_node(bic_frame3,pedal_rod1);
bic_node* bic_pedal_rod2 = new bic_node(bic_pedal_rod,pedal_rod1);
bic_node* bic_spokes[num_spokes];
bic_node* bic_pedals = new bic_node(bic_frame_main, pedals);

int win_width = 640;
int win_height = 480;

void struct_frame();
void struct_frame1();
void struct_frame2();
void struct_frame3();
void struct_frame4();

void struct_front_wheel_pad1();
void struct_wheel();
void struct_pedal_rod();
void struct_pedals();
void struct_wheel_axel();
void struct_spoke();

void tri(float, float, float);
void horizontal_cylinder(float);
void normal_cylinder(float,float);
void normal_cube(float, float, float);
void spoke();

void bicycle_frame();
void init_structures();

float len_frame1 = 5.601f;
float len_frame2 = 2.52f;
float len_frame3 = 5.801;
float horizontal_tilt_frame1 = 10.17f;
float angle_frame2_1 = 85.0f;
float angle_frame3_1 = 90.0f;
float angle_frame4_3 = 60.0f;
float dist_frame4_1 = 2.0f;
float len_frame4 = len_frame1/(sin(angle_frame4_3 * PI/180));
float wheel_pad = .25f;
float len_wheel_pad = 5.0f;
float wheel_radius = 2.0f;
float wheel_thickness = 0.05f;
float pedal_rod_l = 0.1f;
float pedal_rod_b = 1.5f;
float pedal_rod_h = 0.1f;
float len_spoke = 0.01f;

void init_structures()
{
    struct_frame();
    bic_frame1->set_glist(frame1);
    bic_frame2->set_glist(frame2);
    bic_frame3->set_glist(frame3);
    bic_frame4->set_glist(frame4);
    bic_front_wheel->set_glist(wheel1);
    bic_front_wheel_pad->set_glist(fwp1);
    bic_pedal_rod->set_glist(pedal_rod1);
    bic_pedal_rod2->set_glist(pedal_rod1);
    bic_pedals->set_glist(pedals);
    bic_front_wheel_axel->set_glist(wheel_axle1);
//    bic_spokes[0]->set_glist(spoke1);
    for(int i = 0; i < num_spokes; i++)
    {
        bic_spokes[i] = new bic_node();
        bic_spokes[i]->set_parent(bic_front_wheel_axel);
        bic_spokes[i]->set_glist(spoke1);
        bic_front_wheel_axel->add_child(bic_spokes[i]);
        bic_spokes[i]->change_params(0,0,0,0,0,30*i);
    }

    bic_frame1->change_params(0,2.0f,0,0,0,-horizontal_tilt_frame1);
//    bic_frame_main->change_params(0,2.0f,0,0,0,-horizontal_tilt_frame1);
//    bic_pedals->change_params(1.5f, 0,-0.5f,0,0,0);

    bic_frame2->change_params(-len_frame1/2,0,0,0,0,0);
    bic_frame3->change_params(len_frame1/2,-1.5f,0,0,0,0);
    bic_frame4->change_params(0,-dist_frame4_1,0,0,0,0);
    bic_front_wheel_pad->change_params(-len_frame2/2,0,wheel_pad/2,0,0,0);
    bic_front_wheel->change_params(-len_wheel_pad/2,0,-wheel_pad/2,0,0,0);
    bic_pedal_rod->change_params(-len_frame3/2,0,0.5f,0,0,0);
    bic_pedal_rod2->change_params(0,0,-1.0f,0,0,180);

    bic_frame_main->add_child(bic_frame1);
    bic_frame1->add_child(bic_frame2);
    bic_frame1->add_child(bic_frame3);
    bic_frame1->add_child(bic_frame4);
    bic_frame2->add_child(bic_front_wheel_pad);
    bic_front_wheel_pad->add_child(bic_front_wheel);
    bic_front_wheel->add_child(bic_front_wheel_axel);
//    bic_front_wheel->add_child(bic_spokes[0]);
    bic_frame3->add_child(bic_pedal_rod);
    bic_pedal_rod->add_child(bic_pedal_rod2);
}

void struct_frame()
{
    struct_frame1();
    struct_frame2();
    struct_frame3();
    struct_frame4();
    struct_wheel();
    struct_front_wheel_pad1();
    struct_pedals();
    struct_pedal_rod();
    struct_spoke();
    struct_wheel_axel();
}

void struct_frame1()
{
    frame1 = glGenLists(1);
    glNewList(frame1, GL_COMPILE);
    horizontal_cylinder(len_frame1);
    glEndList();
}

void struct_front_wheel_pad1()
{
    fwp1 = glGenLists(1);
    glNewList(fwp1,GL_COMPILE);
//    glTranslatef(-len_frame2/2,0,0.5f);
//    glRotatef(90,1,0,0);
    horizontal_cylinder(len_wheel_pad);
    glEndList();
}

void struct_frame2()
{
    frame2 = glGenLists(1);
    glNewList(frame2,GL_COMPILE);
//    glTranslatef(-len_frame1/2,0,0);
    glRotatef(angle_frame2_1,0,0,1.0f);
    horizontal_cylinder(len_frame2);
    glEndList();
}

void struct_frame3()
{
    frame3 = glGenLists(1);
    glNewList(frame3, GL_COMPILE);
//    glTranslatef(len_frame1/2,-1.5f,0);
    glRotatef(angle_frame3_1,0,0,1.0f);
    horizontal_cylinder(len_frame3);
    glEndList();
}

void struct_frame4()
{
    frame4 = glGenLists(1);
    glNewList(frame4, GL_COMPILE);
//    glTranslatef(0,-dist_frame4_1,0);
    glRotatef(90-angle_frame4_3,0,0,-1.0f);
    horizontal_cylinder(len_frame4);
    glEndList();
}

void struct_wheel()
{
    wheel1 = glGenLists(1);
    glNewList(wheel1, GL_COMPILE);
//    glTranslatef(-len_frame2,0,0);
    //normal_cylinder(wheel_radius, wheel_thickness);
    glColor3f(0,0,0);
    glutSolidTorus(wheel_thickness,wheel_radius,32,32);
    glEndList();
}

void struct_pedal_rod()
{
    pedal_rod1 = glGenLists(1);
    glNewList(pedal_rod1,GL_COMPILE);
    //glColor3f(0,0,0);
    normal_cube(pedal_rod_l,pedal_rod_b,pedal_rod_h);
    glEndList();
}

void struct_pedals()
{
    pedals = glGenLists(1);
    glNewList(pedals, GL_COMPILE);
//    tri(0,0,0);
    glEndList();
}

void struct_spoke()
{
    spoke1 = glGenLists(1);
    glNewList(spoke1,GL_COMPILE);
    spoke();
    glTranslatef(0,wheel_thickness,0);
    spoke();
    glEndList();
}

void struct_wheel_axel()
{
    wheel_axle1 = glGenLists(1);
    glNewList(wheel_axle1,GL_COMPILE);
    glPushMatrix();
    GLUquadricObj *f1;
    glColor3f(0,0,0);
    f1 = gluNewQuadric();
    gluCylinder(f1,0.1f,0.11f,wheel_thickness,32,32);
    glPopMatrix();
    glEndList();

}


void spoke()
{
    glPushMatrix();
    glColor3f(0.6f,0.6f,0.6f);
    GLUquadricObj *f1;
    f1 = gluNewQuadric();
    glTranslatef(0,wheel_thickness,0);
    glTranslatef(-wheel_radius,0.0f,0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(f1,0.01f,0.01f,wheel_radius,32,32);
    glPopMatrix();
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

void normal_cylinder(float radius, float thickness)
{
    glPushMatrix();
    glColor3f(0,0,0);
    GLUquadricObj* f2;
    f2 = gluNewQuadric();
    glTranslatef(0,0,-thickness/2);
    gluCylinder(f2,radius,radius,thickness,32,32);
    glPopMatrix();
}

void normal_cube(float l, float b, float h)
{
    glPushMatrix();
    glColor3f(0,0,0);
    glScalef(l,b,h);
    glTranslatef(-0.5f,-0.5f,0);
    glutSolidCube(1);
//    glutWireCube(1);
    glPopMatrix();
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
//    glColor3f(0,0,0);
   // bic_pedal_rod->render_tree();
    //normal_cube(1,1,1);
//    normal_cylinder(wheel_radius,wheel_thickness);
   // bic_frame2->render_tree();
}