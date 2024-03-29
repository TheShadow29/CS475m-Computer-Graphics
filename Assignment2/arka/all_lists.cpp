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
using namespace std;

#define PI 3.14159265

GLuint frame1;
GLuint frame2;
GLuint frame3;
GLuint frame4;
GLuint frame5;
GLuint fwp1;
GLuint wheel1;
GLuint wheel2;
GLuint spoke1;
GLuint pedal_rod1;
GLuint wheel_axle1;
GLuint wheel_axle2;
GLuint pedal_shaft1;
GLuint pedals1;
GLuint handle_bar1;
GLuint seat1;
GLuint handle2;
GLuint rider1;
GLuint rider_legs1;

const int num_spokes = 12;

bic_node* bic_frame_main = new bic_node ();
bic_node* bic_frame1 = new bic_node(bic_frame_main, frame1);
bic_node* bic_frame2 = new bic_node(bic_frame1, frame2);
bic_node* bic_frame3 = new bic_node(bic_frame1,frame3);
bic_node* bic_frame4 = new bic_node(bic_frame1,frame4);
bic_node* bic_frame5 = new bic_node(bic_frame1,frame5);
bic_node* bic_front_wheel_pad = new bic_node(bic_frame1,fwp1);
bic_node* bic_front_wheel = new bic_node(bic_front_wheel_pad,wheel1);
bic_node* bic_back_wheel = new bic_node(bic_frame5,wheel1);
bic_node* bic_front_wheel_axel = new bic_node(bic_front_wheel,wheel_axle1);
bic_node* bic_back_wheel_axel = new bic_node(bic_back_wheel,wheel_axle1);
bic_node* bic_pedal_rod = new bic_node(bic_frame3,pedal_rod1);
bic_node* bic_pedal_rod2 = new bic_node(bic_pedal_rod,pedal_rod1);
bic_node* bic_spokes[num_spokes];
bic_node* bic_spokes1[num_spokes];
bic_node* bic_pedals1 = new bic_node(bic_pedal_rod, pedals1);
bic_node* bic_pedals2 = new bic_node(bic_pedal_rod2,pedals1);
bic_node* bic_pedal_shaft = new bic_node(bic_pedal_rod,pedal_shaft1);
bic_node* bic_handle_bar = new bic_node(bic_frame2,handle_bar1);
bic_node* bic_seat = new bic_node(bic_frame4,seat1);
bic_node* bic_handle_right = new bic_node(bic_handle_bar,handle2);
bic_node* bic_handle_left = new bic_node(bic_handle_bar,handle2);
bic_node* bic_rider[2];
bic_node* bic_rider_leg[2];


int win_width = 640;
int win_height = 480;

void struct_frame();
void struct_frame1();
void struct_frame2();
void struct_frame3();
void struct_frame4();
void struct_frame5();

void struct_front_wheel_pad1();
void struct_wheel();
void struct_pedal_rod();
void struct_pedals();
void struct_wheel_axel();
void struct_back_wheel_axel();
void struct_spoke();
void struct_pedal_shaft();
void struct_handle_bar();
void struct_seat();
void struct_handle();
void struct_bic_rider();
void struct_bic_rider_legs();

void tri(float, float, float);
void horizontal_cylinder(float);
void normal_cylinder(float,float);
void normal_cube(float, float, float);
void spoke();
void rider_up();
void rider_down();

void bicycle_frame();
void init_structures();
void update_bic_rider_angles();

float len_frame1 = 5.601f;
float len_frame2 = 3.05f;
float len_frame3 = 5.801;
float len_frame5 =  4.20f;
float dist_frame5 = 4.10f;
float horizontal_tilt_frame1 = 10.17f;
float angle_frame2_1 = 85.0f;
float angle_frame3_1 = 90.0f;
float angle_frame4_3 = 60.0f;
float angle_frame5 = 50.0f;
float dist_frame4_1 = 2.0f;
float len_frame4 = len_frame1/(sin(angle_frame4_3 * PI/180));
float wheel_pad = .25f;
float len_wheel_pad = 3.2f;
float wheel_radius = 2.0f;
float wheel_thickness = 0.1f;
float dist_back_wheel = 2.1f;
float pedal_rod_l = 0.1f;
float pedal_rod_b = 1.5f;
float pedal_rod_h = 0.1f;
float len_spoke = 0.01f;
float dist_of_pedal_rod_from_frame = 0.5f;
float len_pedal_shaft = 1.0f;
float pedal_l = 0.05f;
float pedal_b = 0.05f;
float pedal_c = 0.5f;
float len_handle_bar = 3.0f;
float dist_of_handle_from_frame = 1.5f;
float seat_l = 0.8f;
float seat_b = 0.5f;
float seat_c = 0.8f;
float len_handle = 0.65f;
float rider_up_l = 3.0f;
float rider_down_l = 4.0f;

float rider_theta1 = 135.0f;
float rider_theta2 = 45.0f;
float phi_pedal = 0.0f;


void init_structures()
{
    struct_frame();
    bic_frame1->set_glist(frame1);
    bic_frame2->set_glist(frame2);
    bic_frame3->set_glist(frame3);
    bic_frame4->set_glist(frame4);
    bic_frame5->set_glist(frame5);
    bic_front_wheel->set_glist(wheel1);
    bic_back_wheel->set_glist(wheel1);
    bic_front_wheel_pad->set_glist(fwp1);
    bic_pedal_rod->set_glist(pedal_rod1);
    bic_pedal_rod2->set_glist(pedal_rod1);
    bic_front_wheel_axel->set_glist(wheel_axle1);
    bic_back_wheel_axel->set_glist(wheel_axle1);
    bic_pedal_shaft->set_glist(pedal_shaft1);
    bic_handle_bar->set_glist(handle_bar1);
    bic_seat->set_glist(seat1);
    bic_handle_right->set_glist(handle2);
    bic_handle_left->set_glist(handle2);


//    bic_spokes[0]->set_glist(spoke1);
    for(int i = 0; i < num_spokes; i++)
    {
        bic_spokes[i] = new bic_node();
        bic_spokes[i]->set_parent(bic_front_wheel_axel);
        bic_spokes[i]->set_glist(spoke1);
        bic_front_wheel_axel->add_child(bic_spokes[i]);
        bic_spokes[i]->change_params(0,0,0,0,0,30*i);
    }
    for(int i = 0; i < num_spokes; i++)
    {
        bic_spokes1[i] = new bic_node();
        bic_spokes1[i]->set_parent(bic_back_wheel_axel);
        bic_spokes1[i]->set_glist(spoke1);
        bic_back_wheel_axel->add_child(bic_spokes1[i]);
        bic_spokes1[i]->change_params(0,0,0,0,0,30*i);
    }
    for(int i = 0; i < 2; i++)
    {
        bic_rider[i] = new bic_node();
        bic_rider[i]->set_parent(bic_seat);
        bic_seat->add_child(bic_rider[i]);
        bic_rider[i]->set_glist(rider1);
        bic_rider_leg[i] = new bic_node();
        bic_rider_leg[i]->set_parent(bic_rider[i]);
        bic_rider_leg[i]->set_glist(rider_legs1);
        bic_rider[i]->add_child(bic_rider_leg[i]);
        cout << "line 194 " << rider_theta1 << endl;
        bic_rider[i]->change_params(0,0,(0.5-i)*1.5f,0,0,-rider_theta1);
//        bic_rider[i]->change_params(0,0,0,0,0,-rider_theta1);
        bic_rider_leg[i]->change_params(rider_up_l,0,0,0,0,90-rider_theta2);
    }
    bic_pedals1->set_glist(pedals1);

    bic_pedals2->set_glist(pedals1);

    bic_frame1->change_params(0,2.0f,0,0,0,-horizontal_tilt_frame1);
//    bic_frame_main->change_params(0,2.0f,0,0,0,-horizontal_tilt_frame1);
//    bic_pedals->change_params(1.5f, 0,-0.5f,0,0,0);

    bic_frame2->change_params(-len_frame1/2,0,0,0,0,0);
    bic_frame3->change_params(len_frame1/2,-1.5f,0,0,0,0);
    bic_frame5->change_params(dist_frame5,-1.6f,0,0,0,0);
    bic_frame4->change_params(0,-dist_frame4_1,0,0,0,0);
    bic_front_wheel_pad->change_params(-len_frame2,0,wheel_pad/2,0,0,0);
    bic_front_wheel->change_params(-len_wheel_pad/2,0,-wheel_pad/2,0,0,0);
    bic_back_wheel->change_params(dist_back_wheel,0.0f,-wheel_pad/2,0,0,0);
    bic_back_wheel_axel->change_params(0,0,0,0,0,0);
    bic_pedal_rod->change_params(-len_frame3/2,0,dist_of_pedal_rod_from_frame,0,0,0);
    bic_pedal_rod2->change_params(0,0,-2*dist_of_pedal_rod_from_frame,0,0,180);
    bic_pedals1->change_params(0,-pedal_rod_b,pedal_c,0,0,0);
    bic_pedals2->change_params(0,-pedal_rod_b,0,0,0,0);
    bic_seat->change_params(len_frame1/2,1.5f,0,0,0,0);
    bic_handle_left->change_params(0,0,len_handle_bar-len_handle,0,0,0);

    bic_frame_main->add_child(bic_frame1);
    bic_frame1->add_child(bic_frame2);
    bic_frame1->add_child(bic_frame3);
    bic_frame1->add_child(bic_frame4);
    bic_frame1->add_child(bic_frame5);
    bic_frame2->add_child(bic_front_wheel_pad);
    bic_frame2->add_child(bic_handle_bar);
    bic_front_wheel_pad->add_child(bic_front_wheel);
    bic_front_wheel->add_child(bic_front_wheel_axel);
    bic_frame5->add_child(bic_back_wheel);
    bic_back_wheel->add_child(bic_back_wheel_axel);
    bic_frame3->add_child(bic_pedal_rod);
    bic_pedal_rod->add_child(bic_pedal_rod2);
    bic_pedal_rod->add_child(bic_pedal_shaft);
    bic_pedal_rod->add_child(bic_pedals1);
    bic_pedal_rod2->add_child(bic_pedals2);
    bic_frame1->add_child(bic_seat);
    bic_handle_bar->add_child(bic_handle_right);
    bic_handle_bar->add_child(bic_handle_left);
    bic_pedal_rod->set_rz(90);
}

void struct_frame()
{
    struct_frame1();
    struct_frame2();
    struct_frame3();
    struct_frame4();
    struct_frame5();
    struct_wheel();
    struct_front_wheel_pad1();
    struct_pedals();
    struct_pedal_rod();
    struct_spoke();
    struct_wheel_axel();
    struct_pedal_shaft();
    struct_handle_bar();
    struct_seat();
    struct_handle();
    struct_bic_rider();
    struct_bic_rider_legs();
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
//    horizontal_cylinder(len_wheel_pad);
//    glTranslatef(0,-len_frame2/2,0);
    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    GLUquadricObj *f1;
    f1 = gluNewQuadric();
    glTranslatef(-len_wheel_pad/2,0.0f,0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(f1,0.1f,0.1f,len_wheel_pad,32,32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    GLUquadricObj *f2;
    f2 = gluNewQuadric();
    glTranslatef(0,0,-.25f);
    glTranslatef(-len_wheel_pad/2,0.0f,0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(f2,0.1f,0.1f,len_wheel_pad,32,32);
    glPopMatrix();
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
void struct_frame5()
{
    frame5 = glGenLists(1);
    glNewList(frame5, GL_COMPILE);
//    glTranslatef(0,-dist_frame4_1,0);
    glRotatef(angle_frame5,0,0,-1.0f);
    horizontal_cylinder(len_frame5);
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

void struct_pedal_shaft()
{
    pedal_shaft1 = glGenLists(1);
    glNewList(pedal_shaft1,GL_COMPILE);
    //normal_cube(dist_of_pedal_rod_from_frame*2,1,1);
    //normal_cylinder(0.1f, dist_of_pedal_rod_from_frame);
    glPushMatrix();
    glColor3f(0,0,0);
    GLUquadricObj* f2;
    f2 = gluNewQuadric();
    glTranslatef(0,0,-dist_of_pedal_rod_from_frame*2);
    gluCylinder(f2,0.1f,0.1f,dist_of_pedal_rod_from_frame*2,32,32);
    glPopMatrix();
    //tri(0,0,0);
    glEndList();
}

void struct_handle_bar()
{
    handle_bar1 = glGenLists(1);
    glNewList(handle_bar1,GL_COMPILE);
    //normal_cube(dist_of_pedal_rod_from_frame*2,1,1);
    //normal_cylinder(0.1f, dist_of_pedal_rod_from_frame);
    glPushMatrix();
    glColor3f(1.0f,0,0);
    GLUquadricObj* f2;
    f2 = gluNewQuadric();
    glTranslatef(dist_of_handle_from_frame,0,-len_handle_bar/2);
    gluCylinder(f2,0.1f,0.1f,len_handle_bar,32,32);
    glPopMatrix();
    //tri(0,0,0);
    glEndList();
}

void struct_handle()
{
    handle2 = glGenLists(1);
    glNewList(handle2,GL_COMPILE);
    //normal_cube(dist_of_pedal_rod_from_frame*2,1,1);
    //normal_cylinder(0.1f, dist_of_pedal_rod_from_frame);
    glPushMatrix();
    glColor3f(0.0,0,0);
    GLUquadricObj* f2;
    f2 = gluNewQuadric();
    glTranslatef(dist_of_handle_from_frame,0,-len_handle_bar/2);
    gluCylinder(f2,0.13f,0.13f,len_handle,32,32);
    glPopMatrix();
    //tri(0,0,0);
    glEndList();
}

void struct_seat()
{
    seat1 = glGenLists(1);
    glNewList(seat1, GL_COMPILE);
//    normal_cube(pedal_l,pedal_b,pedal_c);
    glPushMatrix();
    glColor3f(0,0,0);
    glScalef(seat_l,seat_b,seat_c);
    // glTranslatef(0,0,-0.0f);
    glutSolidCube(1);
//    glutWireCube(1);
    glPopMatrix();
    glEndList();
}

void struct_pedals()
{
    pedals1 = glGenLists(1);
    glNewList(pedals1, GL_COMPILE);
//    normal_cube(pedal_l,pedal_b,pedal_c);
    glPushMatrix();
    glColor3f(0,0,0);
    glScalef(pedal_l,pedal_b,pedal_c);
    glTranslatef(-0.5f,-0.5f,-0.5f);
    glutSolidCube(1);
//    glutWireCube(1);
    glPopMatrix();
    glEndList();
}

void struct_bic_rider()
{
    rider1 = glGenLists(1);
    glNewList(rider1,GL_COMPILE);
    rider_up();
    glEndList();
}


void struct_bic_rider_legs()
{
    rider_legs1 = glGenLists(1);
    glNewList(rider_legs1,GL_COMPILE);
    rider_down();
    glEndList();
}

void rider_up()
{
    glPushMatrix();
    glColor3f(0.0f,0.0f,1.0f);
    GLUquadricObj *f1;
    f1 = gluNewQuadric();
//    glTranslatef(-len_cylinder/2,0.0f,0.0f);
//    glRotatef(45.0f,0,0,1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(f1,0.3f,0.5f,rider_up_l,32,32);
    glPopMatrix();
}
void rider_down()
{
    glPushMatrix();
    glColor3f(0,0,1);
//    glTranslatef(rider_up_l,0,0.0f);
//    tri(0,0,0);
    GLUquadricObj *f1;
    f1 = gluNewQuadric();
//    glTranslatef(-rider_up_l/2,0,0.0f);
//    glRotatef(-45.0f,0,0,1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(f1,0.5f,0.3f,rider_down_l,32,32);
    glPopMatrix();
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
    gluCylinder(f1,0.05f,0.05f,wheel_radius,32,32);
    glPopMatrix();
}
void update_bic_rider_angles()
{
    phi_pedal = bic_pedal_rod->get_rz();
    float del_theta1;
    float del_theta2;
    float ped_rad = pedal_rod_b;
    float omega = -1;
    del_theta1 = (ped_rad * omega * sin((phi_pedal - rider_theta2)* PI/180)) / (rider_up_l * sin((rider_theta1 + rider_theta2))* PI/180);
    del_theta2 = -(ped_rad * omega * sin((rider_theta1 + phi_pedal)* PI/180))/(rider_down_l * sin((rider_theta1 + rider_theta2)* PI/180));
   // del_theta1 =1;
    //del_theta2 = 1;
    rider_theta1 += del_theta1;
    rider_theta2 += del_theta2;
    for(int i = 0; i < 2; i++)
    {
        cout << "line 194 th1 " << rider_theta1 << endl;
        cout << "line 195 th2 " << rider_theta2 << endl;
        cout << "line 196 phi " << phi_pedal << endl;
        cout << "line 197 delt1 " << del_theta1 << endl;
        cout << "line 198 delt2 " << del_theta2 << endl;
        bic_rider[i]->change_params(0,0,(0.5-i)*1.5f,0,0,-rider_theta1);
//        bic_rider[i]->change_params(0,0,0,0,0,-rider_theta1);
        bic_rider_leg[i]->change_params(rider_up_l,0,0,0,0,90-rider_theta2);
    }
   /*if (rider_theta1 > 180)
    {
        rider_theta1 = rider_theta1 - 360;
    }
    if (rider_theta1 < -180)
    {
        rider_theta1 = rider_theta1 - 360;
    }
    if (rider_theta2 > 180)
    {
        rider_theta2 = rider_theta2 - 360;
    }
    if (rider_theta2 < -180)
    {
        rider_theta2 = rider_theta2 - 360;
    }
    if (phi_pedal > 180)
    {
        phi_pedal = phi_pedal - 360;
    }
    if (phi_pedal < 180)
    {
        phi_pedal = phi_pedal - 360;
    }*/
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