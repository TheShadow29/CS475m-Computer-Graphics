#include <cmath>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
// #include <SOIL/SOIL.h>
#include "lighting_class.hpp"
#include "./bicycle/all_lists.cpp"

using namespace std;

GLuint tex_buff_id;     //create buffer to hold the image
GLfloat *uvs;
GLuint texName;
float cam1_rx = 0, cam1_rz = 0;
float cam1_ex = 0, cam1_ez = 0;
float angle = 0.0;
bool cam1_set = false;
bool cam2_set = false;

bool L_check = false;
GLfloat light_ambient[] = {0.0,0.0,0.0,1.0};
//GLubyte checkImage[checkImageHeight][checkImageWidth][4];

//GLuint tex_coord_id;    //id of texture coordinate variable in the shader
//GLuint tex_id;          //id of texture variable
//GLubyte* image_data;    //image will contain raw color information

unsigned char* texture_image;
int width_text_img;
int heigh_text_img;
float l=10,b=10,h=15;

void draw_cube_room();
void draw_quad_room();
void draw();
void inp_texture();
void gen_texture();
void tri(float, float, float);
void light_init(void);
void camera_pos(char);
void rect(float w, float h, int num);
void draw_rect_room(float, float , float);
void update_cam1();

void inp_texture()
{
   // texture_image = SOIL_load_image("wooden_texture.jpg", &width_text_img, &heigh_text_img, 0, SOIL_LOAD_RGB);
}
//void mytexture(int k) {
//    int i, j, c;
//    for (i = 0; i<checkImageHeight; i++)
//        for (j = 0; j<checkImageWidth; j++) {
//            c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
//            checkImage[i][j][0] = (GLubyte)c;
//            checkImage[i][j][1] = (GLubyte)0;
//            checkImage[i][j][2] = (GLubyte)0;
//            checkImage[i][j][3] = (GLubyte)255;
//        }
//}
void loadBMP_custom(const char * imagepath){

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

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

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

void gen_texture3()
{
    glPushMatrix();
glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
     glEnable(GL_COLOR_MATERIAL);
    loadBMP_custom("./pic_frame3.bmp");
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texName);

    
    glScalef(10,10,15);
        glScalef(0.1,0.1,1);
        glBegin(GL_QUADS);
        /*floor*/
        glColor3f(1,1,1);
        
        // GLfloat white[] = {1,1,1};
        // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-0.99);
        glTexCoord2f(0.0, 1.0); glVertex3f(-1,1,-0.99);
        glTexCoord2f(1.0, 1.0); glVertex3f(1,1,-0.99);
        glTexCoord2f(1.0, 0.0); glVertex3f(1,-1,-0.99);
        glEnd();
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void gen_texture2()
{
    glPushMatrix();
       // glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        //glEnable(GL_COLOR_MATERIAL);
    loadBMP_custom("./wooden_texture1.bmp");
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texName);

    
    glScalef(10,10,15);
    glNormal3f(0,1,0);
        glBegin(GL_QUADS);
        /*floor*/
        
        GLfloat white[] = {1,1,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
        //glColor3f(1,1,1);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,1);
        glTexCoord2f(0.0, 1.0); glVertex3f(1,-1,1);
        glTexCoord2f(1.0, 1.0); glVertex3f(1,-1,-1);
        glTexCoord2f(1.0, 0.0); glVertex3f(-1,-1,-1);
        glEnd();
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void gen_texture()
{
//     glPopMatrix();
    glPushMatrix();
    glScalef(10,10,15);

    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glEnd();

    //glDisable(GL_TEXTURE_2D);


    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glEnd();
    glPopMatrix();


}


void draw_quad_room(float l, float b, float h)
{
    glPushMatrix();
    glColor3f(0,0,0);
    glScalef(l,b,h);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_QUADS);
/* Floor */

    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
/* Ceiling */
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
/* Walls */
    // glVertex3f(-1,-1,1);
    // glVertex3f(1,-1,1);
    // glVertex3f(1,1,1);
    // glVertex3f(-1,1,1);
   // ********************************** //

    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    // ******************************* //

    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);

    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);

    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();
}

void draw_rect_room(float l, float b, float h)
{
    
    glPushMatrix();

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0,0,0);
    glScalef(l,b,h);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glRotatef(90,1,0,0);
    glPushMatrix();
    //back walll
    glTranslatef(0, 0, -1.01);
    rect(2,2,100);
    glPopMatrix();

    glPushMatrix();
    //floor
    glTranslatef(0,-1.01,0);
    glRotatef(90, 1,0,0);
    glNormal3f(0,1,0);
    rect(2,2,100);
    glPopMatrix();

    glPushMatrix();
    //ceiling
    glTranslatef(0,1.01,0);
    glRotatef(90,1,0,0);
    rect(2,2,100);
    glPopMatrix();

    glPushMatrix();
    //left wall
    GLfloat surface_color[] = {1,0,0};
    //glColor3f(1,0,0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, surface_color);
    glTranslatef(-1.01,0,0);
    glRotatef(90,0,1,0);
    rect(2,2,100);
    glPopMatrix();

    glPushMatrix();
    //right wall
    glColor3f(1,0,0);
    glTranslatef(1.01,0,0);
    glRotatef(90,0,-1,0);
    rect(2,2,100);
    glPopMatrix();

//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();
}

void update_cam1()
{
    cam1_ex = bic_frame_main->tx;
    cam1_ez = bic_frame_main->tz;
    float orient = bic_frame2->ry;
    float radius  = 1;
    float sign ;
    if (orient != 0) {
        float tan_theta = tan(orient * PI / 180);
        tan_theta = tan_theta < 0 ? -1 * tan_theta : tan_theta;
        radius = .1 * 12.3255 / tan_theta;
    }
    float frame_ry = bic_frame2->ry;
    if ( frame_ry < 360 && frame_ry > 180) {
        orient = 360 - orient;
        sign = 1;
    }
    if (frame_ry > 0 && frame_ry < 180) {
        orient = orient;
        sign = -1;
    }
   float delta_x = (1)*cos((orient) * PI / 180);
   float delta_z = (1)*sin((orient) * PI / 180);
//    //orient = orient < 0? -1*orient : orient;
    cam1_rx = cam1_ex -(radius)*cos((angle+orient) * PI / 180) ;//  - delta_x;
    cam1_rz = cam1_ez -sign*(radius)*sin((angle +orient) * PI / 180);// - delta_z;
   cout << "line 312 orient " << bic_frame2->ry << " angle " << angle << endl;
//    cout << "line 366 cam1_ex " << 1 + cam1_ex << " cam1_tz " << cam1_ez << endl;
//    cout << "line 313 cam1_rx " << cam1_rx << " cam1_rz " << cam1_rz << endl;
    cout << "line 334 sign" << sign << endl;

    glLoadIdentity();
    gluLookAt( cam1_ex, 1, cam1_ez, cam1_rx, -1, cam1_rz, 0, 1, 0);

//            gluLookAt(cam1_x, 0, cam1_z,1,0, 1, 0, 1, 0);
//    glutPostRedisplay();

}

void update_cam2()
{
    // cam1_ex = bic_frame_main->tx;
    // cam1_ez = bic_frame_main->tz;
    // cout << "line 351" << endl;
    // glLoadIdentity();
    // gluLookAt( 1+cam1_ex, 1, cam1_ez, cam1_ex, -1, cam1_ez, 0, 1, 0);

    cam1_ex = bic_frame_main->tx;
    cam1_ez = bic_frame_main->tz;
    float orient = bic_frame2->ry;
    float radius  = 1;
    float sign ;
    if (orient != 0) {
        float tan_theta = tan(orient * PI / 180);
        tan_theta = tan_theta < 0 ? -1 * tan_theta : tan_theta;
        radius = .1 * 12.3255 / tan_theta;
    }
    float frame_ry = bic_frame2->ry;
    if ( frame_ry < 360 && frame_ry > 180) {
        orient = 360 - orient;
        sign = 1;
    }
    if (frame_ry > 0 && frame_ry < 180) {
        orient = orient;
        sign = -1;
    }
   float delta_x = (1)*cos((orient) * PI / 180);
   float delta_z = (1)*sin((orient) * PI / 180);
//    //orient = orient < 0? -1*orient : orient;
    cam1_rx = cam1_ex -(radius)*cos((angle) * PI / 180) ;//  - delta_x;
    cam1_rz = cam1_ez -sign*(radius)*sin((angle) * PI / 180);// - delta_z;
   // cout << "line 312 orient " << bic_frame2->ry << " angle " << angle << endl;
//    cout << "line 366 cam1_ex " << 1 + cam1_ex << " cam1_tz " << cam1_ez << endl;
//    cout << "line 313 cam1_rx " << cam1_rx << " cam1_rz " << cam1_rz << endl;
     // cout << "line 334 sign" << sign << endl;

    glLoadIdentity();
    gluLookAt( cam1_ex, 10, cam1_ez, cam1_rx , 0, cam1_rz  , 0, 1, 0);

}


void draw_cube_room()
{
    glPushMatrix();
    glColor3f(0,0,0);
    glScalef(10,10,8);
    glutWireCube(1);
    glPopMatrix();
}


void light_init(void)
{
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, -10.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0,0.0,0.0,1.0};
    //GLfloat light_ambient[] = {0.8,0.5,0.1,1.0};`
   // glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv ( GL_LIGHT0 , GL_POSITION , light_position );
    glLightfv ( GL_LIGHT0 , GL_DIFFUSE , light_diffuse );
    glLightfv ( GL_LIGHT0 , GL_SPECULAR , light_specular );
     glLightfv ( GL_LIGHT0 , GL_AMBIENT , light_ambient );

    glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void camera_pos(char key)
{
    //gluLookAt => eye, center, up
    switch (key)
    {
        case '1':
            cam1_set = true;
            cam2_set = false;
            update_cam1();
           //  glLoadIdentity();
            // gluLookAt(cam1_ex, 0, cam1_ez,cam1_rx,0, cam1_rz, 0, 1, 0);
//            gluLookAt(cam1_x, 0, cam1_z,1,0, 1, 0, 1, 0);
            glutPostRedisplay();
            break;
        case '2':
//            glLoadIdentity();
            cam1_set = false;
            cam2_set = true;
            update_cam2();
            glutPostRedisplay();
            break;
        case '3':
            glLoadIdentity();
            cam1_set  = false;
            cam2_set = false;
            gluLookAt(0.9*l, 0.9*b, 0.9*h, 0, 0, 0, 0, 1, 0);
            glutPostRedisplay();
            break;
    }
}

void rect(float w, float h, int num)
{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(-w/2,-h/2,0);
    for (float w1 = 0; w1 < w; w1+=w/num)
    {
        for (float h1 = 0; h1 < h; h1+=h/num)
        {
            // cout << "line 328 w1 " << w1 << " h1 " << h1 << endl;
            //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            //glEnable(GL_COLOR_MATERIAL);
            glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glVertex3f(w1, h1, 0);
            glNormal3f(0,1,0);
            glVertex3f(w1, h1 + h/num, 0);
            glNormal3f(0,1,0);
            glVertex3f(w1 + w/num, h1 + h/num, 0);
            glNormal3f(0,1,0);
            glVertex3f(w1 + w/num, h1, 0);
            glEnd();
        }
    }
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void draw()
{
    // inp_texture(
    // GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
    // GLfloat light_diffuse[] = {0.7, 0.7, 0.5, 1.0};
    // GLfloat light_specular[] = {1.0,0.0,0.0,1.0};
    // GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glShadeModel(GL_SMOOTH);
    // glEnable(GL_DEPTH_TEST);
    // glLightfv ( GL_LIGHT0 , GL_POSITION , light_position );
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // // glLightfv ( GL_LIGHT0 , GL_DIFFUSE , light_diffuse );
    // glLightfv ( GL_LIGHT0 , GL_SPECULAR , light_specular );


    light_init();
    draw_rect_room(10,10,15);
    //draw_quad_room(10,10,15);
    glPushMatrix();
    // glScalef(0.5,0.5,0.5);
    glTranslatef(0,-5,0);
    draw_cycle();
    glPopMatrix();
    gen_texture();
    gen_texture3();
    gen_texture2();

//    draw_cube_room();
}