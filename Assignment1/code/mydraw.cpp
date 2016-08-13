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
#include "related_functions.cpp"

#define ESC 27

//Display callback
void display( void )
{
    //This clears the colorbuffer (current window)
    glClear(GL_COLOR_BUFFER_BIT);
//    disp_canv_array(canvas);
    canvas->display_to_screen();
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
    switch(key)
    {
        //Exit on pressing escape
        case ESC:
            exit(0);
            break;
        //Do something when 'C' is pressed
        case 'N':
            InitCanvas();
            break;
        case 'C':
            canvas->clear();
            break;
        case '1':
            line_mode = !line_mode;
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
            left_button_function(x,y);
            disp_mouse_pointer_click(mouse_point_clicks);
        }
        if (button == GLUT_RIGHT_BUTTON)
        {
            mouse_point_clicks.pop_back();
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
