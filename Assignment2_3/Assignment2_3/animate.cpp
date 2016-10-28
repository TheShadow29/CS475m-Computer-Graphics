#include <GL/glut.h>
#include<iostream>
#include<vector>
#include "all_animate.cpp"
using namespace std;



//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key)
  {
    case 27:           // exit
      exit(0);
    default:
          break;
  }

  if (key == 27)
    exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
  }
  glutPostRedisplay();
}

void display(void)
{
  glClearColor(1,1,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //draw_cycle();

  draw_all();
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
  //glutFullScreen();
  glutSpecialFunc(processSpecialKeys);
  init();
  init_structures();
  glutMainLoop();
  return 0;
}
