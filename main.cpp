#include <GL/glut.h>
#include <GL/glu.h>
#include <cstdio>

int RotateXaxis = 0;
int RotateYaxis = 0;
int RotateZaxis = 0;

enum Face
{
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum Direction
{
    CLOCKWISE,
    ANTICLOCKWISE
};

enum Color
{
    RED,
    ORANGE,
    BLUE,
    GREEN,
    YELLOW,
    WHITE,
    NONE
};

struct Cubie
{
    float x;
    float y;
    float z;

    int xIndex;
    int yIndex;
    int zIndex;

    int colors[6];
};

Cubie cube[27];

struct Rotation
{
    bool active;

    Face face;

    bool clockwise;

    float angle;
};

Rotation currentRotation = {false, FRONT, true, 0.0f};

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

void setColor(Color color)
{
    switch (color)
    {
    case RED:
        glColor3f(1, 0, 0);
        break;
    case ORANGE:
        glColor3f(1, 0.5, 0);
        break;
    case BLUE:
        glColor3f(0, 0, 1);
        break;
    case GREEN:
        glColor3f(0, 1, 0);
        break;
    case YELLOW:
        glColor3f(1, 1, 0);
        break;
    case WHITE:
        glColor3f(1, 1, 1);
        break;
    default:
        glColor3f(0.2f, 0.2f, 0.2f);
    }
}

void drawFace(int a, int b, int c, int d, float r, float g, float bb)
{
    glColor3f(r, g, bb);

    glBegin(GL_QUADS);

    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);

    glEnd();
}

void drawSticker(Face face, Color color)
{
    setColor(color);

    if (face == FRONT)
    {
        glBegin(GL_QUADS);

        glVertex3f(-12, -12, 15.1);
        glVertex3f(12, -12, 15.1);
        glVertex3f(12, 12, 15.1);
        glVertex3f(-12, 12, 15.1);

        glEnd();
    }

    if (face == BACK)
    {
        glBegin(GL_QUADS);

        glVertex3f(-12, -12, -15.1);
        glVertex3f(-12, 12, -15.1);
        glVertex3f(12, 12, -15.1);
        glVertex3f(12, -12, -15.1);

        glEnd();
    }

    if (face == LEFT)
    {
        glBegin(GL_QUADS);

        glVertex3f(-15.1, -12, -12);
        glVertex3f(-15.1, -12, 12);
        glVertex3f(-15.1, 12, 12);
        glVertex3f(-15.1, 12, -12);

        glEnd();
    }

    if (face == RIGHT)
    {
        glBegin(GL_QUADS);

        glVertex3f(15.1, -12, 12);
        glVertex3f(15.1, -12, -12);
        glVertex3f(15.1, 12, -12);
        glVertex3f(15.1, 12, 12);

        glEnd();
    }

    if (face == UP)
    {
        glBegin(GL_QUADS);

        glVertex3f(-12, 15.1, -12);
        glVertex3f(-12, 15.1, 12);
        glVertex3f(12, 15.1, 12);
        glVertex3f(12, 15.1, -12);

        glEnd();
    }

    if (face == DOWN)
    {
        glBegin(GL_QUADS);

        glVertex3f(-12, -15.1, 12);
        glVertex3f(-12, -15.1, -12);
        glVertex3f(12, -15.1, -12);
        glVertex3f(12, -15.1, 12);

        glEnd();
    }
}

// Returns true if this cubie belongs to the layer currently being animated
// for the given face.
bool isInRotatingLayer(const Cubie &cubie, Face face)
{
    switch (face)
    {
    case FRONT:
        return cubie.zIndex == 1;
    case BACK:
        return cubie.zIndex == -1;
    case LEFT:
        return cubie.xIndex == -1;
    case RIGHT:
        return cubie.xIndex == 1;
    case UP:
        return cubie.yIndex == 1;
    case DOWN:
        return cubie.yIndex == -1;
    }
    return false;
}

void drawCubie(const Cubie &cubie)
{
    glPushMatrix();

    if (currentRotation.active && isInRotatingLayer(cubie, currentRotation.face))
    {
        switch (currentRotation.face)
        {
        case FRONT:
            glRotatef(currentRotation.angle, 0, 0, 1);
            break;
        case BACK:
            glRotatef(-currentRotation.angle, 0, 0, 1);
            break;
        case RIGHT:
            glRotatef(currentRotation.angle, 1, 0, 0);
            break;
        case LEFT:
            glRotatef(-currentRotation.angle, 1, 0, 0);
            break;
        case UP:
        case DOWN:
            glRotatef(currentRotation.angle, 0, 1, 0);
            break;
        }
    }

    glTranslatef(cubie.x, cubie.y, cubie.z);

    // Plastic body
    drawFace(0, 1, 5, 4, 0.2f, 0.2f, 0.2f);
    drawFace(3, 2, 6, 7, 0.2f, 0.2f, 0.2f);
    drawFace(0, 3, 7, 4, 0.2f, 0.2f, 0.2f);
    drawFace(1, 2, 6, 5, 0.2f, 0.2f, 0.2f);
    drawFace(4, 5, 6, 7, 0.2f, 0.2f, 0.2f);
    drawFace(0, 1, 2, 3, 0.2f, 0.2f, 0.2f);

    if (cubie.colors[FRONT] != NONE)
        drawSticker(FRONT, (Color)cubie.colors[FRONT]);

    if (cubie.colors[BACK] != NONE)
        drawSticker(BACK, (Color)cubie.colors[BACK]);

    if (cubie.colors[LEFT] != NONE)
        drawSticker(LEFT, (Color)cubie.colors[LEFT]);

    if (cubie.colors[RIGHT] != NONE)
        drawSticker(RIGHT, (Color)cubie.colors[RIGHT]);

    if (cubie.colors[UP] != NONE)
        drawSticker(UP, (Color)cubie.colors[UP]);

    if (cubie.colors[DOWN] != NONE)
        drawSticker(DOWN, (Color)cubie.colors[DOWN]);

    glPopMatrix();
}

void drawRubiksCube()
{
    for (int i = 0; i < 27; i++)
    {
        drawCubie(cube[i]);
    }
}

// Rotates the four side stickers of a cubie that belong to the layer
// being turned. Each face has its own 4-cycle of neighbouring faces.
void rotateStickerColors(Cubie &cubie, Face face, Direction direction)
{
    int temp;

    switch (face)
    {
    case FRONT:
        if (direction == CLOCKWISE)
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[LEFT];
            cubie.colors[LEFT] = temp;
        }
        else
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[LEFT];
            cubie.colors[LEFT] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = temp;
        }
        break;

    case BACK:
        if (direction == CLOCKWISE)
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[LEFT];
            cubie.colors[LEFT] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = temp;
        }
        else
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[LEFT];
            cubie.colors[LEFT] = temp;
        }
        break;

    case LEFT:
        if (direction == CLOCKWISE)
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[FRONT];
            cubie.colors[FRONT] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[BACK];
            cubie.colors[BACK] = temp;
        }
        else
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[BACK];
            cubie.colors[BACK] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[FRONT];
            cubie.colors[FRONT] = temp;
        }
        break;

    case RIGHT:
        if (direction == CLOCKWISE)
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[BACK];
            cubie.colors[BACK] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[FRONT];
            cubie.colors[FRONT] = temp;
        }
        else
        {
            temp = cubie.colors[UP];
            cubie.colors[UP] = cubie.colors[FRONT];
            cubie.colors[FRONT] = cubie.colors[DOWN];
            cubie.colors[DOWN] = cubie.colors[BACK];
            cubie.colors[BACK] = temp;
        }
        break;

    case UP:
        if (direction == CLOCKWISE)
        {
            temp = cubie.colors[FRONT];
            cubie.colors[FRONT] = cubie.colors[LEFT];
            cubie.colors[LEFT] = cubie.colors[BACK];
            cubie.colors[BACK] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = temp;
        }
        else
        {
            temp = cubie.colors[FRONT];
            cubie.colors[FRONT] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = cubie.colors[BACK];
            cubie.colors[BACK] = cubie.colors[LEFT];
            cubie.colors[LEFT] = temp;
        }
        break;

    case DOWN:
        if (direction == CLOCKWISE)
        {
            temp = cubie.colors[FRONT];
            cubie.colors[FRONT] = cubie.colors[LEFT];
            cubie.colors[LEFT] = cubie.colors[BACK];
            cubie.colors[BACK] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = temp;
        }
        else
        {
            temp = cubie.colors[FRONT];
            cubie.colors[FRONT] = cubie.colors[RIGHT];
            cubie.colors[RIGHT] = cubie.colors[BACK];
            cubie.colors[BACK] = cubie.colors[LEFT];
            cubie.colors[LEFT] = temp;
        }
        break;
    }
}

void rotateLayer(Face face, Direction direction)
{
    for (int i = 0; i < 27; i++)
    {
        if (!isInRotatingLayer(cube[i], face))
            continue;

        int oldX = cube[i].xIndex;
        int oldY = cube[i].yIndex;
        int oldZ = cube[i].zIndex;

        switch (face)
        {
        case FRONT:
            if (direction == CLOCKWISE)
            {
                cube[i].xIndex = -oldY;
                cube[i].yIndex = oldX;
            }
            else
            {
                cube[i].xIndex = oldY;
                cube[i].yIndex = -oldX;
            }
            break;

        case BACK:
            if (direction == CLOCKWISE)
            {
                cube[i].xIndex = oldY;
                cube[i].yIndex = -oldX;
            }
            else
            {
                cube[i].xIndex = -oldY;
                cube[i].yIndex = oldX;
            }
            break;

        case LEFT:
            if (direction == CLOCKWISE)
            {
                cube[i].yIndex = oldZ;
                cube[i].zIndex = -oldY;
            }
            else
            {
                cube[i].yIndex = -oldZ;
                cube[i].zIndex = oldY;
            }
            break;

        case RIGHT:
            if (direction == CLOCKWISE)
            {
                cube[i].yIndex = -oldZ;
                cube[i].zIndex = oldY;
            }
            else
            {
                cube[i].yIndex = oldZ;
                cube[i].zIndex = -oldY;
            }
            break;

        case UP:
            if (direction == CLOCKWISE)
            {
                cube[i].zIndex = -oldX;
                cube[i].xIndex = oldZ;
            }
            else
            {
                cube[i].zIndex = oldX;
                cube[i].xIndex = -oldZ;
            }
            break;

        case DOWN:
            if (direction == CLOCKWISE)
            {
                cube[i].zIndex = -oldX;
                cube[i].xIndex = oldZ;
            }
            else
            {
                cube[i].zIndex = oldX;
                cube[i].xIndex = -oldZ;
            }
            break;
        }

        cube[i].x = cube[i].xIndex * 30;
        cube[i].y = cube[i].yIndex * 30;
        cube[i].z = cube[i].zIndex * 30;

        rotateStickerColors(cube[i], face, direction);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -250.0f);

    glRotatef(RotateXaxis, 1, 0, 0);
    glRotatef(RotateYaxis, 0, 1, 0);
    glRotatef(RotateZaxis, 0, 0, 1);

    drawRubiksCube();

    glutSwapBuffers();
}

void startRotation(Face face, bool clockwise)
{
    if (currentRotation.active)
        return;

    currentRotation.active = true;
    currentRotation.face = face;
    currentRotation.clockwise = clockwise;
    currentRotation.angle = 0.0f;
    printf("Face = %d  Clockwise = %d\n", face, clockwise);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'F':
        startRotation(FRONT, true);
        break;
    case 'f':
        startRotation(FRONT, false);
        break;

    case 'B':
        startRotation(BACK, true);
        break;
    case 'b':
        startRotation(BACK, false);
        break;

    case 'U':
        startRotation(UP, true);
        break;
    case 'u':
        startRotation(UP, false);
        break;

    case 'D':
        startRotation(DOWN, true);
        break;
    case 'd':
        startRotation(DOWN, false);
        break;

    case 'L':
        startRotation(LEFT, true);
        break;
    case 'l':
        startRotation(LEFT, false);
        break;

    case 'R':
        startRotation(RIGHT, true);
        break;
    case 'r':
        startRotation(RIGHT, false);
        break;
    case 'x':
        RotateXaxis += 5;
        // printf("RotateXaxis = %d\n", RotateXaxis);
        break;
    case 'X':
        RotateXaxis -= 5;
        // printf("RotateXaxis = %d\n", RotateXaxis);
        break;
    case 'y':
        RotateYaxis += 5;
        // printf("RotateYaxis = %d\n", RotateYaxis);
        break;
    case 'Y':
        RotateYaxis -= 5;
        // printf("RotateYaxis = %d\n", RotateYaxis);
        break;
    case 'Z':
        RotateZaxis += 5;
        // printf("RotateZaxis = %d\n", RotateZaxis);
        break;
    case 'z':
        RotateZaxis -= 5;
        // printf("RotateZaxis = %d\n", RotateZaxis);
    }
}

void updateRotation(int value)
{
    if (currentRotation.active)
    {
        if (currentRotation.clockwise)
            currentRotation.angle += 5.0f;
        else
            currentRotation.angle -= 5.0f;

        if (currentRotation.angle >= 90.0f ||
            currentRotation.angle <= -90.0f)
        {
            currentRotation.angle = 90.0f * (currentRotation.clockwise ? 1 : -1);

            rotateLayer(
                currentRotation.face,
                currentRotation.clockwise ? CLOCKWISE : ANTICLOCKWISE);

            currentRotation.active = false;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(16, updateRotation, 0);
}

void initCube()
{
    int index = 0;

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            for (int z = -1; z <= 1; z++)
            {
                cube[index].xIndex = x;
                cube[index].yIndex = y;
                cube[index].zIndex = z;

                cube[index].x = x * 30;
                cube[index].y = y * 30;
                cube[index].z = z * 30;

                // First remove all stickers
                for (int c = 0; c < 6; c++)
                {
                    cube[index].colors[c] = NONE;
                }

                // Assign initial Rubik's cube colors

                if (z == 1)
                    cube[index].colors[FRONT] = RED;

                if (z == -1)
                    cube[index].colors[BACK] = ORANGE;

                if (x == -1)
                    cube[index].colors[LEFT] = GREEN;

                if (x == 1)
                    cube[index].colors[RIGHT] = BLUE;

                if (y == 1)
                    cube[index].colors[UP] = WHITE;

                if (y == -1)
                    cube[index].colors[DOWN] = YELLOW;

                index++;
            }
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Rubik's Cube");

    init();
    initCube();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateRotation, 0);

    glutMainLoop();

    return 0;
}
