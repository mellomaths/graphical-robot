#include <Windows.h>
#include <iostream>
#include <GL/glut.h>

#define PI 3.141592654
#define tAnima 5.0
#define deltaT 33

using namespace std;

float tamanhoHaste1, tamanhoHaste2, tamanhoHaste3, tamanhoHasteTotal;

float anguloEntreHastes1E2, anguloEntreHastes2E3, anguloMaximo, anguloMinimo, incremento;

void draw(void);
void keyboard(unsigned char key, int x, int y);
void setTimer(int value);
void reshapeWindow(GLsizei w, GLsizei h);

int main(int argc, char** argv)
{
	tamanhoHaste1 = 6;
	tamanhoHaste2 = 4;
	tamanhoHaste3 = 2;
	tamanhoHasteTotal = tamanhoHaste1 + tamanhoHaste2 + tamanhoHaste3;

	anguloEntreHastes1E2 = anguloEntreHastes2E3 = 0;
	anguloMaximo = PI / 2;
	anguloMinimo = -PI / 2;

	incremento = 0.1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Braço Mecânico 2D");
	glutPositionWindow(200, 100);
	glutReshapeWindow(200, 400);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, tamanhoHasteTotal, -tamanhoHasteTotal, tamanhoHasteTotal);

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(deltaT, setTimer, 1);

	glutReshapeFunc(reshapeWindow);

	glutMainLoop();
	return 0;

}
void draw(void) {

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(20);

	// Definindo a Haste 1
	glBegin(GL_LINES);

	glColor3f(0, 0, 1);
	glVertex2f(0.0, 0.0);
	glVertex2f(tamanhoHaste1, 0.0);

	glEnd();


	// Definindo a Haste 2 a partir da Haste 1
	// Multiplicando a matriz identidade do modelview com a translação e em seguida com a de rotação
	// Muda referencial para a ponta da primeira haste
	glTranslatef(tamanhoHaste1, 0, 0); // Gerando uma matriz de transformação

	glRotatef(180.0 * anguloEntreHastes1E2 / PI, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(tamanhoHaste2, 0.0);

	glEnd();
	
	// Definindo a Haste 3 a partir da Haste 2
	glTranslatef(tamanhoHaste2, 0, 0);
	glRotatef(180.0 * anguloEntreHastes2E3 / PI, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);

	glColor3f(0, 1, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(tamanhoHaste3, 0.0);

	glEnd();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

	if (key == 27) exit(0);


	if (key == 119) // Key: W
	{
		// Aumenta incremento de angulo entre haste 1 e 2
		incremento = incremento + 0.1;
	} 
	else if (key == 115) // Key: S
	{
		// Diminui incremento de angulo entre haste 1 e 2
		incremento = incremento - 0.1;

	} 
	else if (key == 97) // Key: A
	{
		// Diminui incremento de angulo entre haste 2 e 3
	}
	else if (key == 100) // Key: D
	{
		// Aumenta incremento de angulo entre haste 2 e 3
	}

}
void setTimer(int value) {

	anguloEntreHastes1E2 = anguloEntreHastes1E2 + incremento;
	if ((anguloEntreHastes1E2 >= anguloMaximo) || (anguloEntreHastes1E2 <= anguloMinimo))
		incremento *= -1;

	anguloEntreHastes2E3 = anguloEntreHastes1E2 * 2;
	glutPostRedisplay();
	glutTimerFunc(deltaT, setTimer, 1);

}
void reshapeWindow(GLsizei w, GLsizei h) {

	if (h == 0) h = 1;

	glViewport(0, 0, h / 2, h);
}