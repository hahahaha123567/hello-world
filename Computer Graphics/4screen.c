// press 1, 2, 3, 4 on keyboard to control the screen

# include <stdio.h>
# include <GL/glut.h>

GLint width;
GLint height;
GLint objSize = 5;
GLint showScreen[] = { 1, 1, 1, 1};
GLfloat go = 0;
GLfloat white[] = {1, 1, 1, 1};
GLfloat color[] = {0, 1, 1, 1};
GLfloat position[] = {0, 10, 0, 1};

void draw ()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(go, 0, 1, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glutSolidTeapot(3);
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    if (showScreen[0]) {
        glViewport(0, height/2+1, width/2-1, height/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-objSize, 0, 0, objSize, 1, 100);
        draw();
    }
    if (showScreen[1]) {
        glViewport(width/2+1, height/2+1, width/2, height/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, objSize, 0, objSize, 1, 100);
        draw();
    }
    if (showScreen[2]) {
        glViewport(0, 0, width/2-1, height/2-1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-objSize, 0, -objSize, 0, 1, 100);
        draw();
    }
    if (showScreen[3]) {
        glViewport(width/2+1, 0, width/2, height/2-1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, objSize, -objSize, 0, 1, 100);
        draw();
    }
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    if (h == 0) {
        h = 1;
    }
    width = w;
    height = h;
}

void key (unsigned char k, int x, int y)
{
    switch (k) {
        case '1': showScreen[0] = 1 ^ showScreen[0]; break;
        case '2': showScreen[1] = 1 ^ showScreen[1]; break;
        case '3': showScreen[2] = 1 ^ showScreen[2]; break;
        case '4': showScreen[3] = 1 ^ showScreen[3]; break;
    }
}

void idle (void)
{
    if (go > 360) {
        go -= 360;
    }
    go += 0.5;
    glutPostRedisplay();
}

int main (int argc, char * argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("4 screen");
    glClearColor(0, 0, 0, 1);
    printf("press 1, 2, 3, 4 on keyboard to control the screen\n");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMainLoop();
}