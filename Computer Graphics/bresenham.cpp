#include <gl\glut.h>
#include <iostream>
using namespace std;

int x_0, y_0, r;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void circle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	bresenham();
	glEnd();
	glFlush();
}

int main(int argc, char ** argv)
{
	cout << "Plsase input x:" << endl;
	cin >> x_0;
	cout << "Plsase input y:" << endl;
	cin >> y_0;
	cout << "Plsase input r:" << endl;
	cin >> r;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("niconiconi");

	init();

	glutDisplayFunc(circle);

	glutMainLoop();
}