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
//    pen_t pen1(5,red1,'d');
//    disp_string_vec(drawing->get_drawing_list(),0);
//    std::vector<std::string> vec = drawing->get_drawing_list();
//    for (int i = 0; i < vec.size(); i++)
//    {
//        std::cout << "line 34" << vec[i] << std::endl;
//    }
    canvas->display_to_screen();
//    std::cout << "next buffer " << std::endl;
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
        std::cout << "Initializing a new canvas" << std::endl;
            mouse_point_clicks.clear();
            InitCanvas();
            break;
        case 'C':
        std::cout << "Clearing the canvas" << std::endl;
            mouse_point_clicks.clear();
            canvas->clear();
            break;
        case '1':
            line_mode = !line_mode;
            if (line_mode){ std::cout << "Entering line mode" << std::endl; mouse_point_clicks.clear();}
            else{ std::cout << "Exiting line mode" << std::endl; mouse_point_clicks.clear();}
            break;
        case '2':
            triangle_mode = !triangle_mode;
            if (triangle_mode)
            {
                std::cout << "Entering triangle mode" << std::endl;
                mouse_point_clicks.clear();
            }
            else{ std::cout << "Exiting triangle mode" << std::endl; mouse_point_clicks.clear();}
            break;
        case 'H':
        std::cout << "Changing Pen color" << std::endl;
        std::cout << "Select New pen color" << std::endl;
            change_pen_color();
            break;
        case 'I':
            std::cout << "Changing Background color" << std::endl;
            std::cout << "Select New Background color" << std::endl;
            change_back_color();
            break;
        case 'J':
            std::cout << "Changing Pen Width" << std::endl;
            std::cout << "Select New Pen Width" << std::endl;
            change_pen_width();
            break;
        case 'S':
            std::cout << "Saving the current drawing" << std::endl;
            save_drawing();
            break;
        case 'L':
        std::cout << "Load drawing" << std::endl;
            load_drawing();
            break;
        case 'G':
            std::cout << "Changing Fill Color" << std::endl;
            std::cout << "Select New Fill Color" << std::endl;
            change_fill_color();
            break;
        case 'F':
        std::cout << "Select any point inside the triangle to be filled" << std::endl;
            fill_triangle();
            break;
        case 'P':
            pen->toggle_pen_mode();
            drawing->store_drawing(pen->toString());
            if (pen->get_mode() == 'd'){ std::cout << "Pen in draw mode" << std::endl;}
            else{ std::cout << "Pen in eraser mode" << std::endl;}
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
            if(!mouse_point_clicks.empty())
            {mouse_point_clicks.pop_back();}
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
