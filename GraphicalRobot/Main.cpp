#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.141592654

using namespace std;

const char* metallicTextureFilename = "./metallic.bmp";

GLuint texture;
GLUquadric* quadricSphere;
GLUquadric* quadricCylinder;

bool textureOn = true;

float robotBaseDiameter = 2.0;
float robotBaseHeight = 5.0;
float robotArmDiameter = 0.3;
float robotArmLength = 4.5;
float robotForearmLength = 3.0;
float robotHandLength = 2.0;
float robotClawLength = 1.0;
float robotArmConnectorDiameter = 0.4;

float eyeDistance = 35.0;
float eyePositionX;
float eyePositionY;
float eyePositionZ;
float viewAngleX = 0.0;
float viewAngleZ = 15.0;

float angleArm = 90.0;
float angleForearm = 45.0;
float angleHand = 0.0;
float angleClawZ = 0.0;
float angleClawY = 0.0;

GLfloat lightPosition[4] = { 0.0f, 30.0f, 0.0f, 0.0f };
GLfloat ambientLight[4] = { 0.19, 0.19, 0.19, 0.0 };

GLuint loadTexture(char* filename);
void initLighting(void);
void initRendering(void);

void handleKeyboardInput(unsigned char key, int x, int y);
void handleWindowReshape(int w, int h);

void drawCylinder(float diameter, float lenght);
void drawCone(float diameter, float lenght);
void drawDisk(float diameterInner, float diameterOuter);
void drawSphere(float diameter);

void drawRobot(void);
void drawRobotBase(void);
void drawArm(float rotationAngle, float translateX, float translateY, float translateZ);
void drawForearm(float rotationAngle, float xPosition, float yPosition, float zPosition);
void drawClaw();
void drawScene(void);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Graphical Robot");

	initLighting();
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeyboardInput);
	glutReshapeFunc(handleWindowReshape);

	glutMainLoop();
	return 0;
}

GLuint loadTexture(const char* filename) {
	GLuint texture;
	int width, height;
	unsigned char* data;

	FILE* file;
	file = fopen(filename, "rb");

	if (file == NULL) return 0;
	width = 1024;
	height = 512;
	data = (unsigned char*)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}//Image with texture

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}


void initLighting(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_COLOR_MATERIAL);
}


void initRendering(void)
{
	quadricSphere = gluNewQuadric();
	quadricCylinder = gluNewQuadric();
	texture = loadTexture(metallicTextureFilename);
}


void handleKeyboardInput(unsigned char key, int x, int y)
{
	switch (key) {
	case 27: //Escape key
		exit(0);
	case 'w': //Increase view angle z axis
		if (viewAngleZ < 180) viewAngleZ += 3;
		glutPostRedisplay();
		break;
	case 's': //Decrease view angle z axis
		if (viewAngleZ > 0) viewAngleZ -= 3;
		glutPostRedisplay();
		break;
	case 'a': //Decrease view angle x axis
		if (viewAngleX > 0) viewAngleX -= 3;
		glutPostRedisplay();
		break;
	case 'd': //Increase view angle x axis
		if (viewAngleX < 180) viewAngleX += 3;
		glutPostRedisplay();
		break;
	case 't': //Use texture or not
		textureOn = !textureOn;
		glutPostRedisplay();
		break;
	case '1': //Increase arm angle
		angleArm += 3;
		if (angleArm < 90) angleArm += 3;
		glutPostRedisplay();
		break;
	case '2': //Decrease arm angle
		angleArm -= 3;
		if (angleArm > -90) angleArm -= 3;
		glutPostRedisplay();
		break;
	case '3': //Increase forearm angle
		if (angleForearm < 90) angleForearm += 3;
		glutPostRedisplay();
		break;
	case '4': //Decrease forearm angle
		if (angleForearm > -90) angleForearm -= 3;
		glutPostRedisplay();
		break;
	case '5': //Increase clamp angle y axis
		if (angleClawY < 60) angleClawY += 3;
		glutPostRedisplay();
		break;
	case '6': //Decrease clamp angle y axis
		if (angleClawY > 0) angleClawY -= 3;
		glutPostRedisplay();
		break;
	}
}


void handleWindowReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
}

void drawCylinder(float diameter, float lenght)
{
	gluCylinder(quadricCylinder, diameter, diameter, lenght, 40.0, lenght * 30.0);
}


void drawCone(float diameter, float lenght)
{
	gluCylinder(quadricCylinder, diameter, 0, lenght, 40.0, lenght * 30.0);
}


void drawDisk(float diameterInner, float diameterOuter)
{
	gluDisk(quadricCylinder, diameterInner, diameterOuter, 40.0, 30.0);
}


void drawSphere(float diameter)
{
	gluSphere(quadricSphere, diameter, 40.0, 40.0);
}


void drawRobot(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	drawRobotBase();

	// Draw left arm
	glPushMatrix();
	drawArm(angleArm, 0.0f, -robotBaseDiameter, -2.0);
	glPopMatrix();

	// Draw right arm
	glPushMatrix();
	drawArm(-angleArm, 0.0f, robotBaseDiameter, -2.0);
	glPopMatrix();	
}


void drawRobotBase(void)
{
	drawCylinder(robotBaseDiameter, robotBaseHeight);
	glTranslatef(0.0f, 0.0f, robotBaseHeight);
	drawDisk(0.0, robotBaseDiameter);
}


void drawArm(float rotationAngle, float translateX, float translateY, float translateZ)
{
	glTranslatef(translateX, translateY, translateZ);
	glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);

	drawCylinder(robotArmDiameter, robotArmLength);

	drawForearm(angleForearm, 0.0f, 0.0f, robotArmLength + robotArmConnectorDiameter / 5);
	drawClaw();
}


void drawForearm(float rotationAngle, float translateX, float translateY, float translateZ)
{
	glTranslatef(translateX, translateY, translateZ);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

	drawSphere(robotArmConnectorDiameter);
	glTranslatef(0.0f, 0.0f, robotArmConnectorDiameter / 5);
	drawCylinder(robotArmDiameter, robotForearmLength);
}


void drawClaw(void)
{
	glTranslatef(0.0f, 0.0f, robotForearmLength + robotArmConnectorDiameter / 5);
	glRotatef(angleClawZ, 0.0f, 0.0f, 1.0f);

	drawSphere(robotArmConnectorDiameter);
	glTranslatef(0.0f, 0.0f, robotArmConnectorDiameter / 2);

	glPushMatrix();

	//draws top part of claw
	glRotatef(angleClawY + 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(robotArmDiameter / 3, robotClawLength);
	glTranslatef(0.0f, 0.0f, robotClawLength + robotArmConnectorDiameter / 15);
	drawSphere(robotArmConnectorDiameter / 3);

	glTranslatef(0.0f, 0.0f, robotArmConnectorDiameter / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);

	drawCylinder(robotArmDiameter / 3, robotClawLength);
	glTranslatef(0.0f, 0.0f, robotClawLength + robotArmConnectorDiameter / 15);
	drawSphere(robotArmConnectorDiameter / 3);

	glTranslatef(0.0f, 0.0f, robotArmConnectorDiameter / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);
	drawCone(robotArmDiameter / 3, robotClawLength);

	glPopMatrix();
	glPushMatrix();

	//draws bottom part of claw
	glRotatef(-angleClawY - 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(robotArmDiameter / 3, robotClawLength);
	glTranslatef(0.0f, 0.0f, robotClawLength + robotArmConnectorDiameter / 15);
	drawSphere(robotArmConnectorDiameter / 3);

	glTranslatef(0.0f, 0.0f, robotArmConnectorDiameter / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);

	drawCylinder(robotArmDiameter / 3, robotClawLength);
	glTranslatef(0.0f, 0.0f, robotClawLength + robotArmConnectorDiameter / 15);
	drawSphere(robotArmConnectorDiameter / 3);

	glTranslatef(0.0f, 0.0f, robotArmConnectorDiameter / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);
	drawCone(robotArmDiameter / 3, robotClawLength);

	glPopMatrix();
}


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	eyePositionX = eyeDistance * cos(viewAngleZ * PI / 180) * cos(viewAngleX * PI / 180);
	eyePositionY = eyeDistance * cos(viewAngleZ * PI / 180) * sin(viewAngleX * PI / 180);
	eyePositionZ = eyeDistance * sin(viewAngleZ * PI / 180);
	if (viewAngleZ < 90)
		gluLookAt(eyePositionX, eyePositionY, eyePositionZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	else
		gluLookAt(eyePositionX, eyePositionY, eyePositionZ, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	drawRobot();

	glutSwapBuffers();
}
