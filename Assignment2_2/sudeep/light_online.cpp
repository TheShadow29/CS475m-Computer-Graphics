#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

float x1 = 0.0f, y1 = 0.0f, z1 = 2.0f;
// x = 0.5f;
// y = 0.5f;
// z = 0.5f;
const GLfloat cutoff = 180.0;
using namespace std;
GLfloat spot_direction[] = {0,0,0};
GLfloat spot_light_position[] = { -0.0, 0.0, 2.0, 1.0 };

void init(void) 
{
   cout << "x:" << x1 << endl;
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_diffuse[] = {0.7, 0.7, 0.5, 1.0};
   GLfloat light_specular[] = {1.0,0.0,0.0,1.0};
   spot_direction[0] = 0;
   spot_direction[1] = -1;
   spot_direction[2] = -1;
   spot_light_position[0] = x1;
   spot_light_position[1] = y1;
   spot_light_position[2] = z1;
   cout << "X1 : " << spot_light_position[0] << endl;
   cout << "y1 : " << y1 << endl;
   cout << "z1 : " << z1 << endl;


   // GLfloat spot_light_position[] = { -0.0, 0.0, 2.0, 1.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv ( GL_LIGHT0 , GL_DIFFUSE , light_diffuse );
    glLightfv ( GL_LIGHT0 , GL_SPECULAR , light_specular );
    glLightfv(GL_LIGHT1, GL_POSITION, spot_light_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &cutoff);
    glLightfv ( GL_LIGHT1 , GL_SPECULAR , light_specular );

   glEnable(GL_LIGHTING);
   //glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   init();
   glColor3f(1.0,0.0,0.0);
   glutSolidSphere (1.0, 20, 16);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void processNormalKeys(unsigned char key, int x, int y) {
  switch(key)
  {
      case 'x':
      case 'X':                  // rotate the along the x axis to view the cycle from different angles
          x1 += 0.1;
          spot_light_position[0] =x1;

           //init();
          //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
          //glEnable(GL_LIGHT1);
          //cout << spot_direction[0] << " " << spot_direction[1] << " " << spot_direction[2] <<endl;
          glutPostRedisplay();
          break;
      case 'y':
      case 'Y':                     // rotate the along the y axis to view the cycle from different angles
          y1 += 0.1;
          spot_light_position[1] = y1;
          // init();
          //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
          //cout << spot_direction[0] << " " << spot_direction[1] << " " << spot_direction[2] <<endl;
          glutPostRedisplay();
          break;
      case 'z':
      case 'Z':                    // rotate the along the z axis to view the cycle from different angles
          z1 += 0.1;
          spot_light_position[2] = z1;
           //init();
         // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
          // cout << spot_direction[0] << " " << spot_direction[1] << " " << spot_direction[2] <<endl;
           glutPostRedisplay();
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

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glutKeyboardFunc(processNormalKeys);
   // init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
