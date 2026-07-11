#include <GL/glut.h>
#include <GL/glu.h>

void init()
{
    // Background color (Black)
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set 3D projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Setting up a standard orthographic volume
    glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
}

float vertices[8][3] =
    {
        {-15.0f, -15.0f, -15.0f}, // v0
        {15.0f, -15.0f, -15.0f},  // v1
        {15.0f, 15.0f, -15.0f},   // v2
        {-15.0f, 15.0f, -15.0f},  // v3
        {-15.0f, -15.0f, 15.0f},  // v4
        {15.0f, -15.0f, 15.0f},   // v5
        {15.0f, 15.0f, 15.0f},    // v6
        {-15.0f, 15.0f, 15.0f}    // v7
};

void display()
{
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Set color to Blue (Red=0.0, Green=0.0, Blue=1.0)
    glColor3f(0.0f, 0.0f, 1.0f);

    // Draw a Quad facing the camera (on the XY plane at Z=0)
    glBegin(GL_QUADS);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[7]);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Quad Drawing"); // Updated title

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}