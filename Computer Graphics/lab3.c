// WASDZC  ：控制相机上下左右前后移动；
// P       ：切换投影方式（正投影与透视投影）；
// O       ：切换渲染方式（填充模式与线框模式）；
// 空格键  ：启动与暂停旋转（桌子与茶壶一起绕桌子中心轴旋转）；
// IKJL    ：控制茶壶前后左右移动
// E       ：控制茶壶开始/暂停旋转

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

float fTranslateTeapot[] = {0.0f, 0.0f, 0.0f};
float fRotate, fRotateTea;
float fScale = 1.0f;

bool bPersp = false;
bool bAnim = false;
bool bAnimTea = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	glPushMatrix();
	glTranslatef(0, 0, 4+1);
	glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	//todo; hint: when operate the teapot, you may need to change some parameters
	glTranslatef(fTranslateTeapot[0], fTranslateTeapot[1], fTranslateTeapot[2]);
	glRotatef(fRotateTea, 0, 1.0f, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}

// since reshape() will be called when the window initials, projection will be set at first
void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;
	
	if (bPersp){
		gluPerspective(60, width/(float)height, 1, 100);
	}
	else {
	    glOrtho(-3 ,3, -3, 3,-100,100);
	}
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle(void)
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': { exit(0); break; }
	case 'p': { bPersp = !bPersp; updateView(wHeight, wWidth); break; }

	case ' ': { bAnim = !bAnim; break; }
	case 'e': { bAnimTea = !bAnimTea; break; }
	case 'o': { bWire = !bWire; break; }

	case 'a': { eye[0] += 0.1; center[0] += 0.1; break; }
	case 'd': { eye[0] -= 0.1; center[0] -= 0.1; break; }
	case 'w': { eye[1] -= 0.1; center[1] -= 0.1; break; }
	case 's': { eye[1] += 0.1; center[1] += 0.1; break; }
	case 'z': { eye[2] -= 0.1; center[2] -= 0.1; break; }
	case 'c': { eye[2] += 0.1; center[2] += 0.1; break; }

	case 'l': { fTranslateTeapot[0] += 0.05; break; }
	case 'j': { fTranslateTeapot[0] -= 0.05; break; }
	case 'i': { fTranslateTeapot[2] -= 0.05; break; }
	case 'k': { fTranslateTeapot[2] += 0.05; break; }
	}
}


void redraw(void)
{
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = {5,5,5,1};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);				

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
			
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();			

	if (bAnim) { 
		fRotate += 0.5f;
	}
	if (bAnimTea) {
		fRotateTea += 0.5f;
	}
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("lab3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}