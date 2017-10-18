# include <gl\glut.h>
# include <windows.h> // Sleep() in windows

GLint windowSize = 500;
GLint x = 250, y = 250, size = 5;

// control the square with 'w', 'a', 's', 'd'
void keyboard (unsigned char key, int curr_x, int curr_y)
{
	if (key == 'w') {
		y -= 10;
	}
	else if (key == 'a') {
		x -= 10;
	}
	else if (key == 's') {
		y += 10;
	}
	else if (key == 'd') {
		x += 10;
	}
	glutPostRedisplay();
}

// control the square with 'up', 'down', 'left', 'right'
void keyboard_special (int key, int curr_x, int curr_y)
{
	if (key == GLUT_KEY_UP) {
		y -= 10;
	}
	else if (key == GLUT_KEY_LEFT) {
		x -= 10;
	}
	else if (key == GLUT_KEY_DOWN) {
		y += 10;
	}
	else if (key == GLUT_KEY_RIGHT) {
		x += 10;
	}
	glutPostRedisplay();
}

// make the square big by click left mouse
void mouse (int button, int state, int curr_x, int curr_y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		size += 4;
	}
	if (size >= 30) {
		size = 5;
	}
	glutPostRedisplay();
}

// drag the square by keep pressing the left mouse
void motion (int curr_x, int curr_y)
{
	x = curr_x;
	y = curr_y;
	glutPostRedisplay();
}

// act with interval
void idle (void)
{
	x += 2;
	Sleep(30);
	glutPostRedisplay();
}

// act with interval
void timer (int value)
{
	y += 1;
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}

void graph (void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (x < 0) {
		x += windowSize;
	}
	if (x > 500) {
		x -= windowSize;
	}
	if (y < 0) {
		y += windowSize;
	}
	if (y > 500) {
		y -= windowSize;
	}
	GLfloat v[4][2] = {
		{ x - size, windowSize - y + size },{ x + size, windowSize - y + size },
		{ x + size, windowSize - y - size },{ x - size, windowSize - y - size }
	};

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	for (int i = 0; i < 4; ++i) {
		glVertex2fv(v[i]);
	}
	glEnd();

	glFlush();
}

int main (int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(windowSize, windowSize);
	glutCreateWindow("I'm a window");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, 500, 0, 500);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);
	glutDisplayFunc(graph);
	glutTimerFunc(20, timer, 0);
	glutMainLoop();
}