/*
####################################
# Developer -- Shelby Rutland
# Date ------- December 11, 2021
####################################
*/

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <cmath>
#include <cstdio>
#include "camera.h"  // Eck's camera API

void init() {
    glEnable(GL_LIGHTING);    // Enable lighting
    glEnable(GL_LIGHT0);      // Turn on a light
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
    glutMouseFunc(trackballMouseFunction);      // Use Eck's mouse function
    glutMotionFunc(trackballMotionFunction);    // Use Eck's motion function
    return;
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // Eck camera
    cameraApply();                                    // Eck camera

    // Use this material for all the vertices of the object
    float object_color[] = {0.15f, 0.25f, 0.39f, 1.0f};   // Prism color
    glMaterialfv(GL_FRONT, GL_DIFFUSE, object_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, object_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, object_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    // Adjust the initial location and orientation of the object
    glTranslatef(-0.5f, -0.5f, -0.5f);
    glRotatef(50.0f, 1.0f, 1.0f, 1.0f);

    glScalef(0.5, 0.5, 0.5);
    
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 10; i++) {
        double angle = 2*3.14159/10 * i;
        double x = cos(angle);
        double y = sin(angle);
        glNormal3f(x, y, 0);
        glVertex3f(x, y, 1);
        glVertex3f(x, y, -1);
    }
    glEnd();

    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 10; i++) {
        double angle = 2*3.14159/10 * i;
        double x = cos(angle);
        double y = sin(angle);
        glVertex3f(x, y, 1);
    }
    glEnd();
    
    glNormal3f(0, 0, -1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 10; i++) {
        double angle = 2*3.14159/10 * i;
        double x = cos(angle);
        double y = sin(angle);
        glVertex3f(x, y, -1);
    }
    glEnd();
    
    glFlush();
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Octagonal Prism");
    glutDisplayFunc(display);
    init();         // Various initializations; mostly lighting.
    glutMainLoop();
    return 0;
}
