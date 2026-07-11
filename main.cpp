#include <GL/glut.h>
#include <GL/glu.h>

void init()
{
    // Background color (Black)
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set 3D projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        45.0, // Field of view
        1.0,  // Aspect ratio
        1.0,  // Near clipping plane
        200.0 // Far clipping plane
    );

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
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

void drawFace(int a, int b, int c, int d, float r, float g, float bColor)
{
    glColor3f(r, g, bColor);
    glBegin(GL_QUADS);

    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);

    glEnd();
}

void drawCubie()
{
    drawFace(0, 1, 5, 4, 1, 0, 0); // Front
    drawFace(3, 2, 6, 7, 0, 1, 0); // Back
    drawFace(0, 3, 7, 4, 0, 0, 1); // Left
    drawFace(1, 2, 6, 5, 1, 1, 0); // Right
    drawFace(4, 5, 6, 7, 1, 0, 1); // Top
    drawFace(0, 1, 2, 3, 0, 1, 1); // Bottom
}

void display()
{
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -80.0f);

    glRotatef(25, 1, 0, 0); // Rotate around X-axis
    glRotatef(30, 0, 1, 0); // Rotate around Y-axis

    // Set color to Blue (Red=0.0, Green=0.0, Blue=1.0)
    glColor3f(0.0f, 0.0f, 1.0f);

    // Draw a Quad facing the camera (on the XY plane at Z=0)
    glBegin(GL_QUADS);

    drawCubie();

    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Quad Drawing"); // Updated title

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}