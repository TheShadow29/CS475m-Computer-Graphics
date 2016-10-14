#include <GL/glut.h>
#include<iostream>
#include<vector>
#include "all_lighting.cpp"

using namespace std;



//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key)
  {
      case 'x':
      case 'X':                  // rotate the along the x axis to view the cycle from different angles
          glRotatef(1.0,1.0,0.0,0.0);
          glutPostRedisplay();
          break;
      case 'y':
      case 'Y':                     // rotate the along the y axis to view the cycle from different angles
          glRotatef(1.,0.0,1.0,0.0);
          glutPostRedisplay();
          break;
      case 'z':
      case 'Z':                    // rotate the along the z axis to view the cycle from different angles
          glRotatef(1,0.0,0.0,1.0);
          glutPostRedisplay();
          break;
      case '1':
          camera_pos('1');
          break;
      case '2':
          camera_pos('2');
          break;
      case '3':
          camera_pos('3');
          break;
      case 'i':
      case 'I':                  // change the look at vector
          glLoadIdentity();
          gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
          glutPostRedisplay();
          break;
    case 27:           // exit
      exit(0);
          break;
  }
  if (key == 27)
    exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
      case GLUT_KEY_LEFT :
          if( angle < 60 || angle >= 300)
              bic_frame2->inc_ry();
          cout << bic_frame2->get_ry() << endl;
          glutPostRedisplay();
          break;

      case GLUT_KEY_RIGHT :
          //float angle1 = bic_frame2->get_ry();
          if( angle <= 60 || angle > 300)
              bic_frame2->dec_ry();
          cout << bic_frame2->get_ry() << endl;
          glutPostRedisplay();
          break;
      case GLUT_KEY_UP :
          bic_pedal_rod->inc_rz();

          bic_front_wheel->inc_rz();
          bic_back_wheel->inc_rz();
          float orientation = bic_frame2->get_ry();
          bic_frame_main ->  dec_angle(angle, orientation);
          angle ++;
          bic_pedal_rod->inc_rz();
          //pdate_bic_rider_angles();
          bic_front_wheel->inc_rz();
          bic_back_wheel->inc_rz();

          if(orientation != 0 && orientation != 360)
          {
              bic_frame_main ->  dec_ry();
          }
          glutPostRedisplay();
          break;
  }
  glutPostRedisplay();
}

void display(void)
{
  glClearColor(1,1,1,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //draw_cycle();

  draw();
  glutSwapBuffers();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 40.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 9.0,  // eye is at (0,0,8)
            0.0, 0.0, 0.0,      // center is at (0,0,0)
            0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("Lighting Modeling");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutFullScreen();
  glutSpecialFunc(processSpecialKeys);
  init();
  init_structures();
  glutMainLoop();
  return 0;
}
