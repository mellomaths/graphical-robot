#include <Windows.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

// Global variables
GLint Width;
GLint Height;
static GLfloat spin = 0.0;

void teapot(void); // Draw Teapot
void spinDisplay(void); // Rotate Teapot
void initLighting(void); // Create Light
void reshape(int width, int height); // Callback to reshape glut window
void display(void); // Callback to draw display
void keyboard(unsigned char key, int x, int y); // Callback to accept keyboard inputs


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Teapot | 4 views");

	initLighting();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}


void teapot(void) 
{
	// glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glutSolidTeapot(2.0);
	// glPopMatrix();
}


void spinDisplay(void)
{
	if (spin > 360.0)
		spin = spin - 360.0;

	glutPostRedisplay();
}


void initLighting(void)
{
	GLfloat lightPosition[] = { 3.0, -3.0, 3.0, 0.0 };

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.0, 0.0, 1.0, 0.0);
}


void reshape(int width, int height)
{
	Width = width;
	Height = height;

	// glViewport(0, 0, width, height);
	glutPostRedisplay();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glPushMatrix();

	// Viewport top-left
	glViewport(0, Height / 2, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -1.0, 5.0); // Creates a Matrix and multiply with Identity
	// glOrtho((x, x), (y, y), (z, z));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0); // Camera position
	teapot();

	// Viewport top-right
	glViewport(Width/2, Height / 2, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	teapot();

	// Viewport bottom-left
	glViewport(0, 0, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	teapot();

	// Viewport bottom-right
	glViewport(Width / 2, 0, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-3.0, 3.0, -3.0, 3.0, 3.0, 6.0); // 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0); // 45 degrees on the X axis
	glRotatef(spin, 0.0, 0.0, 1.0); // X degrees on the Z axis depending on the "spin" variable
	teapot();

	// glPopMatrix();

	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	cout << key;
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		spin = spin - 2.0;
		spinDisplay();
		break;
	case 'd':
		spin = spin + 2.0;
		spinDisplay();
		break;
	default:
		return;
	}

}

