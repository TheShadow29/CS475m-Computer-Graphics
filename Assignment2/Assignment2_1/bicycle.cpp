#include <GL/glut.h>
#include<iostream>
#include<vector>
#include "all_lists.cpp"

using namespace std;


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 'r':
            bic_front_wheel->inc_rz(); // rotate the front wheel  only
            glutPostRedisplay();
            break;
        case 'b':                     // rotate the back wheel only
            bic_back_wheel->inc_rz();
            glutPostRedisplay();
            break;
        case 't':
            bic_frame2->inc_ry();  // move the front the wheel 
            glutPostRedisplay();
            break;
        case 'w':                      // move the wheels and rider pedals the bicycle
            bic_pedal_rod->inc_rz();
            update_bic_rider_angles();
            bic_front_wheel->inc_rz();
            bic_back_wheel->inc_rz();
            glutPostRedisplay();
            break;
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
            }
    
    glutPostRedisplay();
}

void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_cycle();

    glutSwapBuffers();
}

void init(void)
{
    // Use depth buffering for hidden surface elimination.
    glEnable(GL_DEPTH_TEST);
    // Setup the view of the cube.
    glMatrixMode(GL_PROJECTION);
    //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
    gluPerspective(80.0, 1.0, 1.0, 20.0);

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
    glutCreateWindow("Hierarchical Modeling");
    glutDisplayFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    init();
    init_structures();
    glutMainLoop();
    return 0;
}
