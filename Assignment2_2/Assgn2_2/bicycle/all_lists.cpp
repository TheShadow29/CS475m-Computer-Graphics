#include <cmath>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "bicycle_class.cpp"

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

GLuint texName1;

GLuint frame1;
GLuint frame2;
GLuint frame3;
GLuint frame4;
GLuint frame5;
GLuint frame6;
GLuint frame7;
GLuint frame8;
GLuint frame9;
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
bic_node* bic_frame6 = new bic_node(bic_frame5,frame6);
bic_node* bic_frame7 = new bic_node(bic_frame5,frame6);
bic_node* bic_frame8 = new bic_node(bic_frame5,frame8);
bic_node* bic_frame9 = new bic_node(bic_frame5,frame8);
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
void struct_frame6();
void struct_frame8();
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

float len_frame1 = 5.601f;
float len_frame2 = 3.05f;
float len_frame3 = 5.801;
float len_frame5 =  1.60f;
float len_frame8 = 2.35f;
float dist_frame5x = 3.30f; // 4.10 - 0.8
float len_frame6 = 2.55f;
float dist_frame5y = 0.7f; 
float horizontal_tilt_frame1 = 10.17f;
float angle_frame2_1 = 85.0f;
float angle_frame3_1 = 90.0f;
float angle_frame4_3 = 60.0f;
float angle_frame5 = 50.0f;
float angle_frame6 = 120.0f;
float dist_frame4_1 = 2.0f;
float len_frame4 = len_frame1/(sin(angle_frame4_3 * PI/180));
float wheel_pad = .25f;
float len_wheel_pad = 3.2f;
float wheel_radius = 2.0f;
float wheel_thickness = 0.05f;
float dist_back_wheel = 3.1f; // 2.1 + 1.0
float pedal_rod_l = 0.1f;
float pedal_rod_b = 1.0f;
float pedal_rod_h = 0.1f;
float len_spoke = 0.01f;
float dist_frame6x = 2.47f; // 1.05 + 1.42
float dist_frame6y = -1.15f; // -1.2+ 0.05
float dist_of_pedal_rod_from_frame = 0.5f;
float len_pedal_shaft = 1.0f;
float pedal_l = 0.05f;
float pedal_b = 0.05f;
float pedal_c = 0.4f;
float len_handle_bar = 3.0f;
float dist_of_handle_from_frame = 1.5f;
float seat_l = 0.8f;
float seat_b = 0.5f;
float seat_c = 0.8f;
float len_handle = 0.65f;
float frame8x = 4.57f; // 0.52 + 4.10 - 0.05
float frame8y = 2.22f; // 0.78 + 1.60 - 0.16

float rider_up_l = 3.0f;
float rider_down_l = 3.85f;
float rider_theta1[2] = {90.0f, 90.0f};   // 122.522
float rider_theta2[2] = {0.0f, 0.0f};
//rider_theta1[0] = 90.0f ;
//rider_theta1[1] = 90.0f;
//rider_theta2[1] = 0.0f;
//rider_theta2[0] = 0.0f;  // 57.8542
float phi_pedal = 0.0f;

void loadBMP_custom1(const char * imagepath){

    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;

    //  glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    // Open the file
    FILE * file = fopen(imagepath,"rb");
    if (!file){printf("Image could not be opened\n"); return;}

    if (fread(header, 1 , 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return;
    }

    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return;
    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    // width = 225;
    // height = 225;
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];


    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName1);
    glBindTexture(GL_TEXTURE_2D, texName1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                 height, 0, GL_BGR, GL_UNSIGNED_BYTE,
                 data);
}
void cylinder_texture1(float len_cylinder)
{
    glPushMatrix();
    float r = 0.1f;
    /* radius */
    // double r=5.0;
    // double height=4.0;
    /* number of side faces */
    int faces=360;
    /* Choose neutral color (white)*/
    glColor3d(1,1,1);
    loadBMP_custom1("./rock.bmp");
    /* Enable 2D Texture*/
    glEnable(GL_TEXTURE_2D);
    /* set current working texture */
    glBindTexture(GL_TEXTURE_2D, texName1);

    /* Disabling these is not necessary in this example,
    * BUT if you have previously enabled GL_TEXTURE_GEN_
    * for other textures,then you need these lines
    */
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glTranslatef(len_cylinder/2,0.0f,0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUAD_STRIP);
    double x, y, z;
    y=len_cylinder;
    for (int i =0; i <= faces; i++) {
         double u = i/ (double) faces;
         x = r*cos(2*M_PI*u);
         z = r*sin(2*M_PI*u);
         /* Bottom vertex*/
         glTexCoord2d(u, 1.0); glVertex3d( x, 0, z );
         /* Top vertex*/
         glTexCoord2d(u, 0.0); glVertex3d( x, y, z );
    }
    glEnd();
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
}


void init_structures()
{
    struct_frame();
    bic_frame1->set_glist(frame1);
    bic_frame2->set_glist(frame2);
    bic_frame3->set_glist(frame3);
    bic_frame4->set_glist(frame4);
    bic_frame5->set_glist(frame5);
    bic_frame6->set_glist(frame6);
    bic_frame7->set_glist(frame6);
    bic_frame8->set_glist(frame8);
    bic_frame9->set_glist(frame8);
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
        cout << "line 194 " << rider_theta1[i] << endl;
        bic_rider[i]->change_params(0,0,(0.5-i)*1.5f,0,0,-rider_theta1[i]);
//        bic_rider[i]->change_params(0,0,0,0,0,-rider_theta1);
        bic_rider_leg[i]->change_params(rider_up_l,0,0,0,0,rider_theta2[i]);
    }
    bic_pedals1->set_glist(pedals1);

    bic_pedals2->set_glist(pedals1);

    bic_frame1->change_params(0,2.0f,0,0,0,-horizontal_tilt_frame1);
//    bic_frame_main->change_params(0,2.0f,0,0,0,-horizontal_tilt_frame1);
//    bic_pedals->change_params(1.5f, 0,-0.5f,0,0,0);

    bic_frame2->change_params(-len_frame1/2,0,0,0,0,0);
    bic_frame3->change_params(len_frame1/2,-1.5f,0,0,0,0);    
    bic_frame4->change_params(0,-dist_frame4_1,0,0,0,0);
    bic_frame5->change_params(dist_frame5x,-dist_frame5y ,0,0,0,0);


    bic_frame6->change_params(dist_frame6x,dist_frame6y,wheel_pad/2,0,0,0);
    bic_frame7->change_params(dist_frame6x,dist_frame6y,-wheel_thickness-wheel_pad/2,0,0,0);
    bic_frame8->change_params(frame8x ,-frame8y ,wheel_pad/2,0,0,0);
    bic_frame9->change_params(frame8x ,-frame8y ,-wheel_pad/2,0,0,0);
    bic_front_wheel_pad->change_params(-len_frame2,0,wheel_pad/2,0,0,0);
    bic_front_wheel->change_params(-len_wheel_pad/2,0,-wheel_pad/2,0,0,0);
    bic_back_wheel->change_params(dist_back_wheel,0.0f,0,0,0,0);
    bic_back_wheel_axel->change_params(0,0,0,0,0,0);
    bic_pedal_rod->change_params(-len_frame3/2,0,dist_of_pedal_rod_from_frame,0,0,00);
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
    bic_frame5->add_child(bic_frame6);
    bic_frame5->add_child(bic_frame7);
    bic_frame1->add_child(bic_frame8);
    bic_frame1->add_child(bic_frame9);
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
}


void struct_frame()
{
    struct_frame1();
    struct_frame2();
    struct_frame3();
    struct_frame4();
    struct_frame5();
    struct_frame6();
    struct_frame8();
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
    cylinder_texture1(len_frame1);
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

//    glColor3f(0.0f,1.0f,0.0f);
    GLUquadricObj *f1;
    f1 = gluNewQuadric();
    glTranslatef(-len_wheel_pad/2,0.0f,0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    GLfloat surface_color[] = {0,1,0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, surface_color);
    gluQuadricOrientation(f1,GLU_INSIDE);
    gluCylinder(f1,0.1f,0.1f,len_wheel_pad,32,32);
    glPopMatrix();

    glPushMatrix();
//    glColor3f(0.0f,0.0f,0.0f);
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
    cylinder_texture1(len_frame2);
    glEndList();
}

void struct_frame3()
{
    frame3 = glGenLists(1);
    glNewList(frame3, GL_COMPILE);
//    glTranslatef(len_frame1/2,-1.5f,0);
    glRotatef(angle_frame3_1,0,0,1.0f);
    cylinder_texture1(len_frame3);
    glEndList();
}

void struct_frame4()
{
    frame4 = glGenLists(1);
    glNewList(frame4, GL_COMPILE);
//    glTranslatef(0,-dist_frame4_1,0);
    glRotatef(90-angle_frame4_3,0,0,-1.0f);
    cylinder_texture1(len_frame4);
    glEndList();
}
void struct_frame5()
{
    frame5 = glGenLists(1);
    glNewList(frame5, GL_COMPILE);
   //glTranslatef(0.52f,0.78f,0);
    glRotatef(angle_frame5,0,0,-1.0f);
    cylinder_texture1(len_frame5);
    glEndList();
}

void struct_frame6()
{
    frame6 = glGenLists(1);
    glNewList(frame6, GL_COMPILE);
//    glTranslatef(0,-dist_frame4_1,0);
    glRotatef(angle_frame6,0,0,-1.0f);
    cylinder_texture1(len_frame6);
    glEndList();
}

void struct_frame8()
{
    frame8 = glGenLists(1);
    glNewList(frame8, GL_COMPILE);
//    glTranslatef(0,-dist_frame4_1,0);
    glRotatef(angle_frame5,0,0,-1.0f);
    cylinder_texture1(len_frame8);
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


void update_bic_rider_angles()
{
    phi_pedal = 90- bic_pedal_rod->get_rz() ;
    float del_theta1[2];
    float del_theta2[2];
    float ped_rad = pedal_rod_b;
    float omega = 1;
    float theta1[2];
    float theta2[2];
    for(int i = 0; i<2; i++)
    {
        theta1[i] =  rider_theta1[i] - 90 ;     // 90 - rider_theta1
        theta2[i] = rider_theta2[i] - theta1[i];
        float num1 = sin((phi_pedal + theta2[i])* PI/180);
        float num2 = sin((phi_pedal - theta1[i])* PI/180);
        float num3 = sin((theta1[i] + theta2[i])* PI/180);
        if( abs(num3) < 0.001)
        {
            del_theta1[i] = (ped_rad*omega*(2*(0.5-i)))/rider_up_l;
            del_theta2[i] = (ped_rad*omega*(2*(0.5-i)))/rider_down_l;
        }
        else
        {
            del_theta1[i] = (ped_rad*omega*(2*(0.5-i))*num1)/(rider_up_l*num3);
            del_theta2[i] = (ped_rad*omega*(2*(0.5-i))*num2)/(rider_down_l*num3);
        }
    
    
   // del_theta1 = (ped_rad * omega * sin((phi_pedal - rider_theta2)* PI/180)) / (rider_up_l * sin((rider_theta1 + rider_theta2))* PI/180);
    //del_theta2 = -(ped_rad * omega * sin((rider_theta1 + phi_pedal)* PI/180))/(rider_down_l * sin((rider_theta1 + rider_theta2)* PI/180));
    //del_theta1 =1;
    //del_theta2 = 1;
    theta1[i] += del_theta1[i];
    theta2[i]+= del_theta2[i];
    rider_theta1[i] = 90 + theta1[i];
    rider_theta2[i] = theta1[i] +theta2[i];
    //for(int i = 0; i < 2; i++)
    //{
        // cout << "line 614 th1 " << rider_theta1[i] << endl;
        // cout << "line 615 th2 " << rider_theta2[i] << endl;
        // //cout << "line 616 phi " << phi_pedal << endl;
        // cout << "line 617 delt1 " << del_theta1[i] << endl;
        // cout << "line 618 delt2 " << del_theta2[i] << endl;
        // cout << "line 619 num3" << num3 << endl;
         bic_rider[i]->change_params(0,0,(0.5-i)*1.5f,0,0,-rider_theta1[i]);
//        bic_rider[i]->change_params(0,0,0,0,0,-rider_theta1);
        bic_rider_leg[i]->change_params(rider_up_l,0,0,0,0,rider_theta2[i]);
    }
    //}
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