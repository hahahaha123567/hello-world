#include <stdio.h>
#include <gl/glut.h>

float fTranslate;
float fRotate;
float fScale     = 1.0f;
int pause = 0;

void draw (void)
{
    GLdouble size = 0.25;

	glPushMatrix();

	// desktop
    glPushMatrix();
        glScalef(5, 4, 1);
        glutWireCube(size);
    glPopMatrix();

	// 4 table legs
	int flag[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
	for (int i = 0; i < 4; ++i) {
		glPushMatrix();
			glScalef(1, 1, 3);
			glTranslatef(1.5 * size * flag[i][0], 1 * size * flag[i][1], 0.7 * size);
			glutWireCube(size);
		glPopMatrix();
	}
	
	glPopMatrix();
}

void display(void)
{
// If want display in wireframe mode
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	glPushMatrix();
		glTranslatef(-2.0f, 0.0f,-6.0f);				// Place the triangle Left
		glTranslatef(0.0f, fTranslate, 0.0f);			// Translate in Y direction
		draw();								// Draw triangle					
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-6.0f);					// Place the triangle at Center
		glRotatef(fRotate, 0, 1.0f, 0);					// Rotate around Y axis
		draw();								// Draw triangle
	glPopMatrix();


	glPushMatrix();
		glTranslatef(2.0f,0.0f,-6.0f);			// Place the triangle Right
		glScalef(fScale, fScale, fScale);		// Scale with the same value in x,y,z direction
		draw();						// Draw triangle						
	glPopMatrix();


	fTranslate += 0.005f;
	fRotate    += 0.5f;
	fScale     -= 0.005f;

	if(fTranslate > 0.5f) fTranslate = 0.0f;
	if(fScale < 0.5f)     fScale     = 1.0f;

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle(void)
{
	if (!pause) {
	    glutPostRedisplay();
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		pause = ~pause;
	}
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow ("Simple GLUT App"); 

    glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);	
    glutMainLoop();
    return 0;
}
