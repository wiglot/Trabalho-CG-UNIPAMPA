
#include <math.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

#define MAXPARTICULAS 100

float angle=0.0,deltaAngle = 0.0,ratio;
bool fire = false;
float x=0.0f,y=1.75f,z=5.0f;
float shootX, shootZ;
float lx=0.0f,ly=0.0f,lz=-1.0f;
GLint snowman_dl;
GLint fall_dl;
int deltaMove = 0;
int width = 640, height = 360;

typedef struct particula{
	float x, z;
	float vx, vz;
	} Particula;

typedef struct snowman{
	float x, z;
	bool live;
	GLuint dl;
	} SnowMan;

SnowMan boneco[36];

Particula *lista[MAXPARTICULAS];
short numParticulas = 0;

Particula* createParticula() {
	
	Particula* nova;
	nova = (Particula*) malloc (sizeof(Particula));
	
	nova->vx = sin(angle);
	nova->vz = -cos(angle);
	nova->x = x;
	nova->z = z;

	return nova;	
}


void moveParticula(Particula* p) {
	int i;
	float d;
	if (p->vx !=0 && p->vz != 0){
		for (i = 0; i < 36; i++)
			if (boneco[i].live){
				d = sqrt((boneco[i].x - p->x)*(boneco[i].x - p->x) + (boneco[i].z - p->z)*(boneco[i].z - p->z) );
				//printf ("%f - %f x %f\n", d, boneco[i].x, boneco[i].z );
				if (d < 0.75 ){
					boneco[i].live = false;
					boneco[i].dl = fall_dl;
					p->vx = p->vz = 0;
					i = 36;
				}
				if (d > 200)
					p->vx = p->vz = 0;
	
			}

		p->x = p->x + 2*(p->vx)*0.1;
		p->z = p->z + 2*(p->vz)*0.1;
	}
}



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

void drawBall() {
	glColor3f(0.5f, 0.0f, 0.0f);

	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.15f,20,20);
	glTranslatef(0.0f ,-0.75f, 0.0f);
}

void drawSnowMan() {


	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body	
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);


// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void drawFallSnowMan() {


	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body	
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);


// Draw Head
	glTranslatef(1.0f, -0.5f, 0.5f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(1.05f, 0.0f, 0.68f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,0.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}


GLuint createDL() {
	GLuint snowManDL;

	// Create the id for the list
	snowManDL = glGenLists(1);

	// start list
	glNewList(snowManDL,GL_COMPILE);

	// call the function that contains the rendering commands
		drawSnowMan();

	// endList
	glEndList();

	return(snowManDL);
}

GLuint createFallDL(){
	GLuint snowManDL;

	// Create the id for the list
	snowManDL = glGenLists(2);

	// start list
	glNewList(snowManDL,GL_COMPILE);

	// call the function that contains the rendering commands
		drawFallSnowMan();

	// endList
	glEndList();

	return(snowManDL);

}

void initScene() {
	int i, j , k;
	snowman_dl = createDL();
	fall_dl = createFallDL();
	glEnable(GL_DEPTH_TEST);
	for(int i = -3, k = 0; i < 3; i++)
		for(int j=-3; j < 3; j++, k++) {
			boneco[k].live = true;
			boneco[k].x = i*10;
			boneco[k].z = j*10;
			boneco[k].dl = snowman_dl;

		}
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
	unsigned int j;
	float nX, nZ;
	nX = x+ i*(lx)*0.1;
	nZ = z+ i*(lz)*0.1;
	for (j = 0; j < 36; j++){
		if (boneco[j].live)
			if (sqrt((boneco[j].x - nX)*(boneco[j].x - nX) + (boneco[j].z - nZ)*(boneco[j].z - nZ) ) < 1.5f){
				break;
			}
	}

	if (j == 36){
		x = nX;
		z = nZ;
		glLoadIdentity();
		gluLookAt(x, y, z, 
			      x + lx,y + ly,z + lz,
				  0.0f,1.0f,0.0f);
	}
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

	for (i = 0; i < numParticulas; i++){			
	//	printf("%f - %f X %f - %f\n", lista[i]->x, lista[i]->z, x, z);
	//	glPushMatrix();
		glTranslatef(lista[i]->x, 0, lista[i]->z);
	//	glCallList(snowman_display_list);;

		drawBall();
		glTranslatef(-lista[i]->x, 0, -lista[i]->z);
		moveParticula(lista[i]);
		glPopMatrix();
	}	

// Draw 36 SnowMen
	
	for(int i = 0; i < 36; i++){
		//if (boneco[i].live){
			glPushMatrix();
			glTranslatef(boneco[i].x,0,boneco[i].z);
			glCallList(boneco[i].dl);;
			glTranslatef(-boneco[i].x,0,-boneco[i].z);

			glPopMatrix();
		}
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
	if (key == 27) 
		exit(0);
	if (key == ' '){
		for (i = 0; i < numParticulas; i++){			
			moveParticula(lista[i]);
		}
	}
		
}

void processMouse(int button, int state, int x, int y) {
	unsigned short i;

	// if both a mouse button, and the ALT key, are pressed  then
	if (state == GLUT_DOWN) {

		// set the color to pure red for the left button
		if (button == GLUT_LEFT_BUTTON) {
			if (numParticulas < MAXPARTICULAS-1){
				lista[numParticulas] = createParticula();
				numParticulas++;
			}

		}else if (button == GLUT_RIGHT_BUTTON){
			for (i = 0; i < numParticulas; i++)
				free (lista[i]);
			numParticulas = 0;
		}
		
	}
}

void processMousePassiveMotion(int x, int y) {
	
	// setting the angle to be relative to the mouse 
	// position inside the window
	if (x < 0 || x > width || y < 0 || y > height)
		deltaAngle = 0.0;
	else{
		x -= width/2;
		if (x < 0)
			deltaAngle = -x/((double)width*5) * x/((double)width*5);
		else
			deltaAngle = x/((double)width*5) * x/((double)width*5);

//		printf ("%f \n", deltaAngle);
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
