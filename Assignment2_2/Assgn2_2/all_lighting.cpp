#include <cmath>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>

#include "lighting_class.hpp"

using namespace std;

unsigned char* texture_image;
int width_text_img;
int heigh_text_img;

void draw_cube_room();
void draw_quad_room();
void draw();
void inp_texture();
void gen_texture();

void inp_texture()
{
    texture_image = SOIL_load_image("wooden_texture.jpg", &width_text_img, &heigh_text_img, 0, SOIL_LOAD_RGB);
}
void gen_texture()
{
    GLuint texture;
    glGenTextures(1,&texture);
    //second argument sets the mip map level
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_text_img, heigh_text_img, GL_RGB, GL_UNSIGNED_BYTE, texture_image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(texture_image);
    glBindTexture(GL_TEXTURE_2D, 0);
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
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);

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

void draw_cube_room()
{
    glPushMatrix();
    glColor3f(0,0,0);
    glScalef(10,10,8);
    glutWireCube(1);
    glPopMatrix();
}

void draw()
{
    inp_texture();
    gen_texture();
    draw_quad_room(10,10,15);
//    draw_cube_room();
}
