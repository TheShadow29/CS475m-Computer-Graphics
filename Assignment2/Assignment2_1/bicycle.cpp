#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "all_lists.cpp"


/* Create display list with Torus and initialize state*/
void init(void)
{
    init_structures();
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    draw_cycle();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

/* Rotate about x-axis when "x" typed; rotate about y-axis
   when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x':
        case 'X':
            glRotatef(30.0,1.0,0.0,0.0);
            glutPostRedisplay();
            break;
        case 'y':
        case 'Y':
            glRotatef(30.,0.0,1.0,0.0);
            glutPostRedisplay();
            break;
        case 'i':
        case 'I':
            glLoadIdentity();
            gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char **argv)
{
    glutInitWindowSize(win_width, win_height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
//    glutFullScreen();
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}