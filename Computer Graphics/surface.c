#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

void quadric()
{
    // create
    GLUquadric * qua = gluNewQuadric();
    gluQuadricOrientation(qua, GLU_OUTSIDE); // GLU_INSIDE
    gluQuadricDrawStyle(qua, GLU_LINE); // GLU_FILL, GLU_SILHOUETTE, GLU_POINT
    gluQuadricNormals(qua, GLU_NONE); // GLU_FLAT, GLU_SMOOTH
    gluQuadricTexture(qua, true);
    // set shape
    gluSphere(qua, 0.5, 100, 100); // gluCylinder(); gluDisk();
    // delete
    gluDeleteQuadric(qua);
}

void bezier2D()
{
    float begin = 0.0f, end = 1.0f;
    GLfloat controlPoint[4][3] = {
        {-1, -1, 0},
        {-1, 1, 0},
        {1, -1, 0},
        {1, 1, 0}
    };
    // pass control points to evaluator
    glMap1f(GL_MAP1_VERTEX_3, begin, end, 3, 4, (GLfloat *)controlPoint[0]);
	glEnable(GL_MAP1_VERTEX_3);
    // calculate curve with evaluator, fitting with 100 points
    glMapGrid1f(100, begin, end);
    glEvalMesh1(GL_LINE, 0, 99);
}

void bezier3D()
{
    GLfloat x_begin = 0.0f, x_end = 1.0f;
    GLfloat z_begin = 0.0f, z_end = 1.0f;
    GLfloat controlPoint[16][3] = {
        { -0.8f, 0.8f, 0.1f },  
        { -0.9f, 0.3f, 0.3f },  
        { -0.9f, -0.2f, 0.3f },  
        { -0.8f, -0.7f, 0.2f },

        { -0.3f, 0.8f, 0.2f },  
        { -0.3f, 0.2f, 0.5f },  
        { -0.25f, -0.2f, 0.6f },  
        { -0.3f, -0.6f, 0.2f },

        { 0.2f, 0.85f, 0.1f },  
        { 0.25f, 0.25f, 0.6f },  
        { 0.3f, -0.2f, 0.4f },  
        { 0.2f, -0.65f, 0.3f },

        { 0.7f, 0.8f, 0.1f },  
        { 0.8f, 0.3f, 0.3f },  
        { 0.75f, -0.2f, 0.3f },  
        { 0.7f, -0.7f, 0.2f }  
    };
    // pass control points to evaluator
    glMap2f(GL_MAP2_VERTEX_3, z_begin, z_end, 3, 4, x_begin, x_end, 12, 4, (GLfloat *)controlPoint);
    glEnable(GL_MAP2_VERTEX_3);
    // calculate curve with evaluator, fitting with 100 points
    glMapGrid2f(100, z_begin, z_end, 100, x_begin, x_end);
    glEvalMesh2(GL_LINE, 0, 99, 0, 99);
    // glEnable(GL_AUTO_NORMAL); // used for light
}

void nurbs3D() 
{
    GLfloat point[] = { 
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f 
    };
    GLfloat controlPoint[16][3] = {
        { -0.8f, 0.8f, 0.1f },  
        { -0.9f, 0.3f, 0.3f },  
        { -0.9f, -0.2f, 0.3f },  
        { -0.8f, -0.7f, 0.2f },

        { -0.3f, 0.8f, 0.2f },  
        { -0.3f, 0.2f, 0.5f },  
        { -0.25f, -0.2f, 0.6f },  
        { -0.3f, -0.6f, 0.2f },

        { 0.2f, 0.85f, 0.1f },  
        { 0.25f, 0.25f, 0.6f },  
        { 0.3f, -0.2f, 0.4f },  
        { 0.2f, -0.65f, 0.3f },

        { 0.7f, 0.8f, 0.1f },  
        { 0.8f, 0.3f, 0.3f },  
        { 0.75f, -0.2f, 0.3f },  
        { 0.7f, -0.7f, 0.2f }  
    };
    // create
    GLUnurbs * nurbs = gluNewNurbsRenderer();
    // set property
	gluNurbsProperty(nurbs, GLU_SAMPLING_TOLERANCE, 10.0f); 
    gluNurbsProperty(nurbs, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
    // set shape
    // gluNurbsCurve();
    gluNurbsSurface(nurbs, 8, point, 8, point, 4 * 3, 3, (GLfloat *)controlPoint, 4, 4, GL_MAP2_VERTEX_3);
    // end
    gluEndSurface(nurbs);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0f, 0.0f, 0.0f);
    // quadric();
    // bezier2D();
    // bezier3D();
    nurbs3D();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("surface");
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}