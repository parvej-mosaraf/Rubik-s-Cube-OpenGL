#include <GL/glut.h>
#include <GL/glu.h>

enum Face // set of face
{
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

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
        500.0 // Far clipping plane
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

float stickerVertices[4][3] =
    {
        {-12.0f, -12.0f, 15.1f},
        {12.0f, -12.0f, 15.1f},
        {12.0f, 12.0f, 15.1f},
        {-12.0f, 12.0f, 15.1f}};

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

void drawSticker(Face face)
{
    if (face == FRONT)
    {
        glColor3f(1, 0, 0); // Red

        glBegin(GL_QUADS);

        glVertex3f(-12, -12, 15.1);
        glVertex3f(12, -12, 15.1);
        glVertex3f(12, 12, 15.1);
        glVertex3f(-12, 12, 15.1);

        glEnd();
    }

    if (face == BACK)
    {
        glColor3f(1, 0.5, 0); // orange

        glBegin(GL_QUADS);

        glVertex3f(-12, -12, -15.1);
        glVertex3f(-12, 12, -15.1);
        glVertex3f(12, 12, -15.1);
        glVertex3f(12, -12, -15.1);

        glEnd();
    }

    if (face == LEFT)
    {
        glColor3f(0, 1, 0); // green

        glBegin(GL_QUADS);

        glVertex3f(-15.1, -12, -12);
        glVertex3f(-15.1, -12, 12);
        glVertex3f(-15.1, 12, 12);
        glVertex3f(-15.1, 12, -12);

        glEnd();
    }

    if (face == RIGHT)
    {
        glColor3f(0, 0, 1); // blue

        glBegin(GL_QUADS);

        glVertex3f(15.1, -12, 12);
        glVertex3f(15.1, -12, -12);
        glVertex3f(15.1, 12, -12);
        glVertex3f(15.1, 12, 12);

        glEnd();
    }

    if (face == TOP)
    {
        glColor3f(1, 1, 1); // white

        glBegin(GL_QUADS);

        glVertex3f(-12, 15.1, -12);
        glVertex3f(-12, 15.1, 12);
        glVertex3f(12, 15.1, 12);
        glVertex3f(12, 15.1, -12);

        glEnd();
    }

    if (face == BOTTOM)
    {
        glColor3f(1, 1, 0); // yellow

        glBegin(GL_QUADS);

        glVertex3f(-12, -15.1, 12);
        glVertex3f(-12, -15.1, -12);
        glVertex3f(12, -15.1, -12);
        glVertex3f(12, -15.1, 12);

        glEnd();
    }
}

void drawCubie(float x, float y, float z, int xIndex, int yIndex, int zIndex)
{
    glPushMatrix();

    glTranslatef(x, y, z);

    // Plastic body
    drawFace(0, 1, 5, 4, 0.2, 0.2, 0.2);
    drawFace(3, 2, 6, 7, 0.2, 0.2, 0.2);
    drawFace(0, 3, 7, 4, 0.2, 0.2, 0.2);
    drawFace(1, 2, 6, 5, 0.2, 0.2, 0.2);
    drawFace(4, 5, 6, 7, 0.2, 0.2, 0.2);
    drawFace(0, 1, 2, 3, 0.2, 0.2, 0.2);

    // Stickers (temporary)
    drawFace(0, 1, 5, 4, 1, 0, 0);
    drawFace(3, 2, 6, 7, 0, 1, 0);
    drawFace(0, 3, 7, 4, 0, 0, 1);
    drawFace(1, 2, 6, 5, 1, 1, 0);
    drawFace(4, 5, 6, 7, 1, 0, 1);
    drawFace(0, 1, 2, 3, 0, 1, 1);

    if (zIndex == 1)
    {
        drawSticker(FRONT);
    }

    if (zIndex == -1)
    {
        drawSticker(BACK);
    }

    if (xIndex == -1)
    {
        drawSticker(LEFT);
    }

    if (xIndex == 1)
    {
        drawSticker(RIGHT);
    }

    if (yIndex == 1)
    {
        drawSticker(TOP);
    }
    if (yIndex == -1)
    {
        drawSticker(BOTTOM);
    }

    glPopMatrix();
}

void drawRubiksCube()
{
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            for (int z = -1; z <= 1; z++)
            {
                drawCubie(
                    x * 30,
                    y * 30,
                    z * 30,
                    x,
                    y,
                    z);
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -250.0f);

    glRotatef(25, 1, 0, 0);
    glRotatef(120, 0, 1, 0);

    drawRubiksCube();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("OpenGL Quad Drawing"); // Updated title

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}