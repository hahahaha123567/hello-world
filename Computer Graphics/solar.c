# include <stdio.h>
# include <gl/glut.h>

GLfloat w = 1280;
GLfloat h = 720;
GLfloat time = 10000;
GLfloat delta_time = 5;

GLfloat sunshinePosition[] = {0, 0, 0, 1};
GLfloat white[] = {1, 1, 1, 1};

enum Planet {
    Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune
} ;
GLfloat radius[] = {6, 1, 2, 2, 1, 6, 6, 3, 3};
GLfloat revolution_radius[] = {0, 0.4+1, 1+1, 2+1, 3.5+1, 5+1, 9+1, 13+1, 16+1};
GLfloat revolution_period[] = {1, 0.25, 0.6, 1, 1.9, 11, 30, 85, 165};
GLfloat planet_color[][4] = { {1, 1, 0, 1},
                            {205/255.0, 149/255.0, 12/255.0, 1}, {255/255.0, 215/215.0, 0/255.0, 1},
                            {0/255.0, 0/255.0, 210/255.0, 1}, {255/255.0, 48/255.0, 48/255.0, 1},
                            {255/255.0, 165/255.0, 79/255.0, 1}, {238/255.0, 207/255.0, 161/255.0, 1},
                            {99/255.0, 184/255.0, 255/255.0, 1}, {28/255.0, 134/255.0, 238/255.0, 1}};

void sunshine ()
{    
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_POSITION, sunshinePosition);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

void draw_planet (enum Planet planet)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, planet_color[planet]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, planet_color[planet]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glRotatef(time/revolution_period[planet], 0, 1, 0);
    glTranslatef(revolution_radius[planet], 0, 0);
    glutSolidSphere(radius[planet]/6, 1000, 1000);
    if (planet == Earth) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, white);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialf(GL_FRONT, GL_SHININESS, 50);
        glRotatef(time/(1.0/12), 0, 1, 0);
        glTranslatef(0.6, 0, 0);
        glutSolidSphere(0.08, 1000, 1000);
    }
    glPopMatrix();
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, w, h);

    sunshine();

    // perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, w/h, 1, 100);

    // model-view and lookat
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 9, 27, 0, 0, 0, 0, 3, -1);

    // draw orbit
    glPushMatrix();
    glColor3f(1, 1, 1);
    glPointSize(1200);    
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    for (float i = 0; i < 360; i += 0.5) {
        glRotatef(i, 0, 1, 0);
        for (int j = 1; j < 9; ++j) {
            glTranslatef(revolution_radius[j], 0, 0);
            glutSolidSphere(0.03, 10, 10);
            glTranslatef(-revolution_radius[j], 0, 0);
        }
    }
    glPopMatrix();

    for (int i = 0; i < 9; ++i) {
        draw_planet(i);
    }
    glutSwapBuffers();
}

void idle (void)
{
    time += delta_time;
    glutPostRedisplay();
}

int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutCreateWindow("Solar System");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}