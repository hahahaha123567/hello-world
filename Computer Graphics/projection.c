# include <stdio.h>
# include <gl/glut.h>

GLfloat rotate_x = 0;
GLfloat rotate_y = 0;
int state = 0;

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); // push() & pop() is better
    glRotatef(rotate_x, 1, 0, 0);
    glRotatef(rotate_y, 0, 1, 0);
    glutWireTetrahedron();

    glFlush();
}

void keyboard (int key, int x, int y) 
{
    state = key;
}

void act (void)
{
    switch (state) {
        case GLUT_KEY_UP: { rotate_x -= 0.02; break; }
        case GLUT_KEY_DOWN: { rotate_x += 0.02; break; }
        case GLUT_KEY_LEFT: { rotate_y -= 0.02; break; }
        case GLUT_KEY_RIGHT: { rotate_y += 0.02; break; }
    }
    glutPostRedisplay();
}

int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Nico");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutIdleFunc(act);
    glutMainLoop();
}