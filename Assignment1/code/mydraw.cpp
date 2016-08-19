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
int counter = 0;
//Display callback
void display( void )
{
    //This clears the colorbuffer (current window)
    glClear(GL_COLOR_BUFFER_BIT);
//    disp_canv_array(canvas);
    pen_t pen1(5,red1,'d');
    for(int i = 20; i < 100; i++)
    {
        point_t a(i,i-10,red1);
       // std::string s = a.toString();
      //  drawing->store_drawing(s);
       a.draw(canvas->get_pixel_array(), pen1);
    }
    std::vector<std::string> vec = drawing->get_drawing_list();
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << "line 34" << vec[i] << std::endl;
    }
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
        case '2':
            triangle_mode = !triangle_mode;
            break;
        case 'H':
            change_pen_color();
            break;
        case 'I':
            change_back_color();
            break;
        case 'J':
            change_pen_width();
            break;
        case 'S':
            save_drawing();
            break;
        case 'L':
            load_drawing();
            break;
        case 'G':
            change_fill_color();
            break;
        case 'F':
            fill_triangle();
            break;
        case 'P':
            pen->toggle_pen_mode();
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

    if (counter == 1)
    {
        win_width = 480;
        win_height = 640;
    }
    if (counter == 0)
    {
        counter += 1;
    }
    std::cout << "counter=" << counter << std::endl;
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
