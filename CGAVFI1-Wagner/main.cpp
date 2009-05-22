#include "falange.h"
#include "mao.h"
#include <math.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

#define MAXPARTICULAS 100

float angle=0.0,deltaAngle = 0.0,ratio;

float x=0.0f,y=1.75f,z=5.0f;

float lx=0.0f,ly=0.0f,lz=-1.0f;
GLint mao_dl;

int deltaMove = 0;
int width = 640, height = 360;

Mao *mao = new Mao();





void changeSize(int w, int h)
	{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
        glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);


	}

GLuint createDL() {
	GLuint DL;

	// Create the id for the list
	DL = glGenLists(1);

	// start list
	glNewList(DL,GL_COMPILE);

	// call the function that contains the rendering commands
		mao->draw();
	// endList
	glEndList();

	return(DL);
}



void initScene() {
	int i, j , k;
	mao->setCarpo(new Carpo(0.1,1.9, 1.0));
	for (i = 0; i< 5; i++)
		mao->setMetacarpo(new MetaCarpo(0.1,1.0+(1+1*0.2)),i);
	for (i = 0; i < 5; i++)
		mao->setProximais(new Falange(1.1, 0.09),i);
	for (i = 0; i< 4; i++)
		mao->setMedias(new Falange(1, 0.09), i);
	for (i = 0; i < 5; i++)
			mao->setDistais(new Falange(0.5, 0.09),i);
	mao->createDLs();
	//mao_dl = createDL();
	glEnable(GL_DEPTH_TEST);

}



void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}


void moveMeFlat(int i) {

	x = x+ i*(lx)*0.1;
	z = z+ i*(lz)*0.1;

	glLoadIdentity();
	gluLookAt(x, y, z,
			  x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);

}

void renderScene(void) {
	unsigned short i;
	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Draw ground

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	glTranslatef(0.0, 0.5, 0.0);
	glRotated(-90,1.0,0.0,0.0);
	mao->draw();
	//glCallList(mao_dl);
	glRotated(90,1.0,0.0,0.0);
	glTranslatef(0.0, -0.5, 0.0);

	glutSwapBuffers();
}

void pressKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
		case GLUT_KEY_UP : deltaMove = 1;break;
		case GLUT_KEY_DOWN : deltaMove = -1;break;
	}

}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	unsigned short i;
	switch (key){
		case  27 : exit(0);
//Polegar
		case ';': mao->addAnguloMetacarpo (4, 0, 0.5);
			   break;
		case '.': mao->addAnguloMetacarpo (4, 0, -0.5);
			   break;
		case '0': mao->addAnguloProximais(4, 0, 1.0);
			   break;
		case 'l': mao->addAnguloProximais(4, 0, -1.0);
			   break;
		case 'p': mao->addAnguloDistais(4, 0, 2.0);
			   break;
		case 'o': mao->addAnguloDistais(4, 0, -2.0);
			   break;
//Indicador
		case ',': mao->addAnguloMetacarpo (3, 0, 0.5);
			   break;
		case 'm': mao->addAnguloMetacarpo (3, 0, -0.5);
			   break;
		case 'k': mao->addAnguloProximais(3, 0, 1.0);
			   break;
		case 'j': mao->addAnguloProximais(3, 0, -1.0);
			   break;
		case 'i': mao->addAnguloMedias(3, 0, 1.0);
			   break;
		case 'u': mao->addAnguloMedias(3, 0, -1.0);
			   break;
		case '8': mao->addAnguloDistais(3, 0, 2.0);
			   break;
		case '7': mao->addAnguloDistais(3, 0, -2.0);
			   break;
//Medio
		case 'n': mao->addAnguloMetacarpo (2, 0, 0.5);
			   break;
		case 'b': mao->addAnguloMetacarpo (2, 0, -0.5);
			   break;
		case 'h': mao->addAnguloProximais(2, 0, 1.0);
			   break;
		case 'g': mao->addAnguloProximais(2, 0, -1.0);
			   break;
		case 'y': mao->addAnguloMedias(2, 0, 1.0);
			   break;
		case 't': mao->addAnguloMedias(2, 0, -1.0);
			   break;
		case '6': mao->addAnguloDistais(2, 0, 2.0);
			   break;
		case '5': mao->addAnguloDistais(2, 0, -2.0);
			   break;
//Anelas
		case 'v': mao->addAnguloMetacarpo (1, 0, 0.5);
			   break;
		case 'c' : mao->addAnguloMetacarpo (1, 0, -0.5);
			   break;
		case 'f': mao->addAnguloProximais(1, 0, 1.0);
			   break;
		case 'd': mao->addAnguloProximais(1, 0, -1.0);
			   break;
		case 'r': mao->addAnguloMedias(1, 0, 1.0);
			   break;
		case 'e': mao->addAnguloMedias(1, 0, -1.0);
			   break;
		case '4': mao->addAnguloDistais(1, 0, 2.0);
			   break;
		case '3': mao->addAnguloDistais(1, 0, -2.0);
			   break;
//Minimo
		case 'x': mao->addAnguloMetacarpo (0, 0, 0.5);
			   break;
		case 'z' : mao->addAnguloMetacarpo (0, 0, -0.5);
			   break;
		case 's': mao->addAnguloProximais(0, 0, 1.0);
			   break;
		case 'a': mao->addAnguloProximais(0, 0, -1.0);
			   break;
		case 'w': mao->addAnguloMedias(0, 0, 1.0);
			   break;
		case 'q': mao->addAnguloMedias(0, 0, -1.0);
			   break;
		case '2': mao->addAnguloDistais(0, 0, 2.0);
			   break;
		case '1': mao->addAnguloDistais(0, 0, -2.0);
			   break;

	}

}

void processMouse(int button, int state, int x, int y) {
//	unsigned short i;
//
//	// if both a mouse button, and the ALT key, are pressed  then
//	if (state == GLUT_DOWN) {
//
//		// set the color to pure red for the left button
//		if (button == GLUT_LEFT_BUTTON) {
//			if (numParticulas < MAXPARTICULAS-1){
//				lista[numParticulas] = createParticula();
//				numParticulas++;
//			}
//
//		}else if (button == GLUT_RIGHT_BUTTON){
//			for (i = 0; i < numParticulas; i++)
//				free (lista[i]);
//			numParticulas = 0;
//		}
//
//	}
}

void processMousePassiveMotion(int x, int y) {

	// setting the angle to be relative to the mouse
	// position inside the window
	if (x < 0 || x > width || y < 0 || y > height)
		deltaAngle = 0.0;
	else{
		x -= width/2;
		if (x < 0)
			deltaAngle = -x/((double)width*2) * x/((double)width*2);
		else
			deltaAngle = x/((double)width*2) * x/((double)width*2);

	}

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("SnowMen from Lighthouse 3D");

	initScene();

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(processMouse);
	glutPassiveMotionFunc(processMousePassiveMotion);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
}
