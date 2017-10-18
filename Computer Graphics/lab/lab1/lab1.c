#include <gl\glut.h>

void star()
{
	GLfloat v[13][2] = {
		{0, 0},
		{0, 0.5}, {0.1, 0.3},
		{0.4, 0.3}, {0.25, 0},
		{0.4, -0.3}, {0.1, -0.3},
		{0, -0.5}, {-0.1, -0.3},
		{-0.4, -0.3}, {-0.25, 0},
		{-0.4, 0.3}, {-0.1, 0.3}
	};
	GLfloat color[7][3] = {
		{1, 1, 1}, // white
		{1, 0, 0}, // red
		{1, 0, 1}, // pink
		{0, 0, 1}, // blue
		{0, 1, 1}, // light blue
		{0, 1, 0}, // green
		{1, 1, 0}  // yellow
	};

	glBegin(GL_POLYGON);
	glColor3fv(color[0]);
	glVertex2fv(v[0]);
	for (GLint i = 1; i <= 6; ++i) {
		glColor3fv(color[i]);
		glVertex2fv(v[2 * i - 1]);
		glVertex2fv(v[2 * i]);
	}
	glColor3fv(color[1]);
	glVertex2fv(v[1]);
	glEnd();

	glFlush();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lab1");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-1, 1, -1, 1);

	glutDisplayFunc(star);

	glutMainLoop();
}