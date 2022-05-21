#include <Windows.h>
#include <stdio.h>
#include <GL/glut.h>

// Callbacks
void displayCallback(void);
void mouseMovementCallback(int x, int y);
void mouseButtonCallback(int button, int state, int x, int y);
void reshapeWindowCallback(GLsizei w, GLsizei h);

// Global variables
GLsizei width, height; // Initial world windows and viewport
float rx, ry; // Initial rectangle position

int main(int argc, char** argv)
{
	width = 600; height = 600;
	rx = 0; ry = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glClearColor(0, 0, 0, 1);
	
	glutPositionWindow(200, 100);
	glutReshapeWindow(width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(displayCallback);
	glutIdleFunc(displayCallback);
	glutMotionFunc(mouseMovementCallback);
	glutMouseFunc(mouseButtonCallback);
	glutReshapeFunc(reshapeWindowCallback);
	
	glutMainLoop();
	return 0;
}

void displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0); // Yellow
	glRectf(100, 100, 300, 200); // Draw yellow rectangle

	glColor3f(1, 0, 0); // Red
	glRectf(rx, ry, 100 + rx, 20 + ry); // Draw red rectangle

	glutSwapBuffers(); // Double color buffer
}


// Responsible to handle mouse movement with button pressed
void mouseMovementCallback(int x, int y)
{
	rx = x;
	ry = height - y;
}


// Responsible to handle button press events
void mouseButtonCallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rx = x;
		ry = height - y;
	}
}


// Responsible to handle window reshapes
void reshapeWindowCallback(GLsizei w, GLsizei h)
{
	height = h;
	width = w;

	// Viewport dimensions
	glViewport(0, 0, width, height); // Default behavior

	// Initialize world coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// World Window dimensions
	gluOrtho2D(0, width, 0, height);
}