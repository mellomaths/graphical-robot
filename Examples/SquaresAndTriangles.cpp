#include <Windows.h>
#include <stdio.h>
#include <GL/glut.h>


void drawGreenSquare(void)
{
	// Define a cor do quadrado como verde
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS); // Begin draw

		glVertex2i(100, 150);
		glVertex2i(100, 100);
		glVertex2i(150, 100);
		glVertex2i(150, 150);

	glEnd();
}

void drawMixedColorSquare(void)
{
	glBegin(GL_QUADS); // Begin draw

	// Define a cor do vértice como: amarela
	glColor3f(1.0, 249.0/255.0, 163.0/255.0);
	glVertex2i(100, 150);

	// Define a cor do vértice como: verde
	glColor3f(169.0/255.0, 1.0, 163.0 / 255.0);
	glVertex2i(100, 100);

	// Define a cor do vértice como: rosa
	glColor3f(249.0/255.0, 163.0/255.0, 1.0);
	glVertex2i(150, 100);

	// Define a cor do vértice como: roxo
	glColor3f(163.0 / 255.0, 169.0 / 255.0, 1.0);
	glVertex2i(150, 150);

	glEnd();
}

void drawRedTriangle(void)
{
	glBegin(GL_TRIANGLES); // Begin draw
	// Define a cor do desenho como vermelha
	glColor3f(1, 0, 0);

		glVertex2f(-0.5, -0.5);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.5, -0.5);

	glEnd();
}

void drawRgbTriangle(void)
{
	glBegin(GL_TRIANGLES); // Begin draw
	
		// Define a cor do vértice como: vermelha
		glColor3f(1, 0, 0);
		glVertex2f(-0.5, -0.5);
	
		// Define a cor do vértice como: verde
		glColor3f(0, 1, 0);
		glVertex2f(0.0, 0.5);
	
		// Define a cor do vértice como: azul
		glColor3f(0, 0, 1);
		glVertex2f(0.5, -0.5);

	glEnd();
}

void display(void)
{
	// Define a cor de fundo da janela como branca
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//drawRedTriangle();
	//drawRgbTriangle();

	glFlush();
}

void displayViewport(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Carrega matriz de identidade

	// Limpa a janela de visualização com a cor do fundo
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//drawGreenSquare();
	//drawMixedColorSquare();

	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void reshapeWindow(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1; // Evita divisão por zero

	glViewport(0, 0, w, h); // Especifica as dimensões da Viewport
	glMatrixMode(GL_PROJECTION); // Inicializa a matriz de projeção
	glLoadIdentity();

	// Estabelece World Window (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
	else
		gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
}

void init(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Janela do OpenGL");

	glutDisplayFunc(displayViewport);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshapeWindow);

	init();
	
	glutMainLoop();
	return 0;
}
