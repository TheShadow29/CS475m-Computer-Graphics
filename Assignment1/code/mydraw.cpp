/*******************************
 *
 * CS475m Assignment 1 Basecode
 *
 * Parag Chaudhuri, 2016
 *
 *******************************/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include "mydraw_class.hpp"
color_t red1 = color_t(1.0f,0.0f,0.0f);
color_t green1 = color_t(0.0f,1.0f,0.0f);
color_t blue1 = color_t(0.0f,0.0f,1.0f);
color_t black1 = color_t(0.0f,0.0f,0.0f);
color_t white1 = color_t(1.0f,1.0f,1.0f);
//color_t bgm = color_t(0.5f, 0.5f, 0.5f);
//Window width
int win_width = 640;
//Window height
int win_height = 480;
void canvas_t::display_to_screen()
{
    GLubyte checkImage[this->height][this->width][3];
    point_t** arr = this->get_pixel_array();
    for(int i = 0; i < this-> height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            checkImage[i][j][0] = (GLubyte) int(arr[i][j].get_point_color().R()*255);
            checkImage[i][j][1] = (GLubyte) int(arr[i][j].get_point_color().G()*255);
            checkImage[i][j][2] = (GLubyte) int(arr[i][j].get_point_color().B()*255);
        }
    }
    glRasterPos2i(0,0);
    glDrawPixels(this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, checkImage);
}
void disp_color_t(color_t elm)
{
    std::cout << "red" << elm.R();
    std::cout << "green" << elm.G();
    std::cout << "blue" << elm.B()<< std::endl;
}

void disp_canv_array(canvas_t* canv)
{
    int w = canv -> getW();
    int h = canv -> getH();
    point_t** arr = canv->get_pixel_array();
    for(int i = 0; i < h; i++)
    {
        for (int j=0; j < w; j++)
        {
            std::cout << "i=" << i << " j=" << j << std::endl;
            disp_color_t(arr[i][j].get_point_color());
            std::cout << std::endl;
        }
    }
    return;
}


//Display callback
void display( void )
{
    //This clears the colorbuffer (current window)
    glClear(GL_COLOR_BUFFER_BIT);
    canvas_t* canvas1 = new canvas_t(win_width, win_height);
    pen_t pen(3, red1, 'd');
    for (int i = 19; i < 100; i++)
    {
        point_t a(i, 2*i+10, red1);
        a.draw(canvas1->get_pixel_array(),pen);
    }
//    point_t a(19,39,red1);
//  a.draw(canvas1->get_pixel_array(), pen);
  //  a.draw_direct(canvas1->get_pixel_array());
    canvas1->display_to_screen();
    std::cout << "next buffer " << std::endl;
    //Flush the framebuffer to the screen
    glutSwapBuffers();
}

//Reshape callback
void reshape( int w, int h )
{
  if  ( h == 0 ) h = 1;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1., 1. );
  glViewport( 0, 0, w, h );

  win_width = w;
  win_height = h;

  glutPostRedisplay();
}

//Keyboard callback
void keyboard( unsigned char key, int x, int y ) {
  switch(key) {
  //Exit on pressing escape
  case 27:
    exit(0);
    break;
    //Do something when 'C' is pressed
  case 'C':
    break;
    //Ignore all other keypresses
  default:
    break;
  }
}

//Mouse callback
void mouse(int button, int state, int x, int y)
{
   if (state == GLUT_DOWN)
     {
       if (button == GLUT_LEFT_BUTTON)
       {
         //Do something when the left mouse button is clicked
       }
     }
   glutPostRedisplay();
}


int main (int argc, char *argv[])
{
//    canvas_t* canvas1 = new canvas_t(win_width, win_height);
//    disp_canv_array(canvas1);

    //disp_color_t(red1);
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize( win_width, win_height );

  //Open a GLUT window
  glutCreateWindow( "MyDraw" );
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMouseFunc( mouse );

  glutMainLoop();

}
