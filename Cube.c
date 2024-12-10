/* Rotating cube with color interpolation */

/* Demonstration of use of homogeneous coordinate
transformations and simple data structure for representing
cube from Chapter 4 */

/*Both normals and colors are assigned to the vertices */
/*Cube is centered at origin so (unnormalized) normals
are the same as the vertex values */

#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
                         {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
                         {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
                        {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
                        {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
                       {1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0},
                       {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};


//Variaveis globais
static GLfloat theta[2][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0} };
static GLint axis = 2;

float scale[2] = { 1.0, 1.0 }; //Escala do cubo

//Posição do cubo
float xCubo[2] = { 0.0,0.0 };
float yCubo[2] = { 0.0,0.0 };

//Selecionar o cubo
int selected = 0;


void tempo()
{
	int i;
	double max = 10000000.0;
	for (i = 0; i < max; i++) {
		(1 / max)* max* max* max / 3.14 + (1 / max) * max * max * max / 3.14 + (1 / max) * max * max * max / 3.14 + (1 / max) * max * max * max / 3.14;
		(1 / max)* max* max* max / 3.14 + (1 / max) * max * max * max / 3.14 + (1 / max) * max * max * max / 3.14 + (1 / max) * max * max * max / 3.14;
	}

}

void polygon(int a, int b, int c , int d)
{

/* draw a polygon via list of vertices */

    glBegin(GL_POLYGON);
    //glColor3fv(colors[a]);
    glNormal3fv(normals[a]);
    glVertex3fv(vertices[a]);
    //glColor3fv(colors[b]);
    glNormal3fv(normals[b]);
    glVertex3fv(vertices[b]);
    //glColor3fv(colors[c]);
    glNormal3fv(normals[c]);
    glVertex3fv(vertices[c]);
    //glColor3fv(colors[d]);
    glNormal3fv(normals[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}


void colorcube(void)
{
    /* Função que mapeia os vértices para as faces do cubo */
    /* map vertices to faces */

    glColor3fv(colors[0]);
    polygon(0, 3, 2, 1);
    glColor3fv(colors[1]);
    polygon(2, 3, 7, 6);
    glColor3fv(colors[2]);
    polygon(0, 4, 7, 3);
    glColor3fv(colors[3]);
    polygon(1, 2, 6, 5);
    glColor3fv(colors[4]);
    polygon(4, 5, 6, 7);
    glColor3fv(colors[5]);
    polygon(0, 1, 5, 4);
}

//Criar um cubo mágico -- Versão sem push e pop
void cuboMagico()
{
	int i, j, k;

	glScalef(0.2, 0.2, 0.2);

	glTranslatef(-2.2 * 2, -2.2 * 2, -2.2 * 2);

	for (i = 0; i < 3; i++) {
		glTranslatef(0.0, 0.0, 2.2);
		for (j = 0; j < 3; j++) {
			glTranslatef(0.0, 2.2, 0.0);
			for (k = 0; k < 3; k++) {
				glTranslatef(2.2, 0.0, 0.0);
				colorcube();
			}
			glTranslatef(-2.2 * 3, 0.0, 0.0);
		}
		glTranslatef(0.0, -2.2 * 3, 0.0);
	}
	glTranslatef(0.0, 0.0, -2.2 * 3);
}

// Criar um cubo mágico -- Versão com push e pop
void cuboMagico2() {
	int i, j, k;

	glPushMatrix();

	glScalef(0.2, 0.2, 0.2);

	glTranslatef(-2.2, -2.2, -2.2);

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++) {
				glPushMatrix();
				glTranslatef(2.2 * i, 2.2 * j, 2.2 * k);
				colorcube();
				glPopMatrix();
			}
	glPopMatrix();
}


// Função que desenha 3 cubos
void desenha3Cubos()
{
    colorcube();
    glTranslatef(2.5,0.0,0.0);
    colorcube();
    glTranslatef(-2.5,0.0,0.0);
    colorcube();
}

// Função que desenha 3 cubos modificado
void desenha3Cubos2()
{

	glPushMatrix();

	glScalef(0.5,0.5,0.5);

	cuboMagico2();
	glPushMatrix();
	glTranslatef(2.5,0.0,0.0);
	cuboMagico2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5,0.0,0.0);
	cuboMagico2();
	glPopMatrix();

	glPopMatrix();
}


// Desenha os eixos X, Y e Z
void desenhaEixos() {
	glBegin(GL_LINES);

	// Eixo X em vermelho
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-2.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);

	// Eixo Y em verde
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -2.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);

	// Eixo Z em azul
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -2.0);
	glVertex3f(0.0, 0.0, 2.0);

	glEnd();
}


void display(void)
{
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity(); // Carrega a matriz identidade

	//cubo 1
	glPushMatrix();

    glTranslatef(xCubo[0], yCubo[0], 0.0);

    // Aplica rotações ao cubo em torno dos eixos X, Y e Z
    glRotatef(theta[0][0], 1.0, 0.0, 0.0); // Rotação em torno do eixo X
    glRotatef(theta[0][1], 0.0, 1.0, 0.0); // Rotação em torno do eixo Y
    glRotatef(theta[0][2], 0.0, 0.0, 1.0); // Rotação em torno do eixo Z


    // Aplica a escala ao cubo
    glScalef(scale[0], scale[0], scale[0]);

	cuboMagico(); // Desenha um cubo mágico
	glPopMatrix();



	//cubo 2
	glPushMatrix();

	glTranslatef(xCubo[1], yCubo[1], 0.0);

	// Aplica rotações ao cubo em torno dos eixos X, Y e Z
	glRotatef(theta[1][0], 1.0, 0.0, 0.0); // Rotação em torno do eixo X
	glRotatef(theta[1][1], 0.0, 1.0, 0.0); // Rotação em torno do eixo Y
	glRotatef(theta[1][2], 0.0, 0.0, 1.0); // Rotação em torno do eixo Z


	// Aplica a escala ao cubo
	glScalef(scale[1], scale[1], scale[1]);

	cuboMagico(); // Desenha um cubo mágico
	glPopMatrix();



    // Desenha um cubo
    //colorcube();


    // Desenha 3 cubos
    //desenha3Cubos();


	// Desenha 3 cubos modificado
	//desenha3Cubos2();

	//glPushMatrix(); // Salva a matriz de transformação atual

	//cuboMagico(); // Desenha um cubo mágico

	//glPopMatrix(); // Restaura a matriz de transformação salva

	//cuboMagico2(); // Desenha um cubo mágico com push e pop


	// Desenha os eixos
	desenhaEixos();



    glFlush();

    //tempo();

    //glutSwapBuffers();
}

void spinCube()
{

	/* Idle callback, spin cube 2 degrees about selected axis */

	theta[selected][axis] += 2.0;
	if (theta[selected][axis] > 360.0) theta[selected][axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{

	/* mouse callback, selects an axis about which to rotate */

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void keyboard(int key, int x, int y) {
	int i;

	if (key == GLUT_KEY_UP) {
		theta[selected][0] -= 2.0;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN) {
		theta[selected][0] += 2.0;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_LEFT) {
		theta[selected][1] -= 2.0;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_RIGHT) {
		theta[selected][1] += 2.0;
		glutPostRedisplay();
	}

	for (i = 0; i < 3; i++) {
		if (theta[selected][i] > 360.0) theta[selected][i] -= 360.0;
		if (theta[selected][i] < -360.0) theta[selected][i] += 360.0;
	}
}




void keyboard2(unsigned char key, int x, int y)
{
    switch (key) {
        case '+': scale[selected] += 0.1; glutPostRedisplay(); break;
        case '-': scale[selected] -= 0.1; glutPostRedisplay(); break;
        case 'W':
        case 'w': yCubo[selected] += 0.1; glutPostRedisplay(); break;
        case 's': yCubo[selected] -= 0.1; glutPostRedisplay(); break;
        case 'a': xCubo[selected] -= 0.1; glutPostRedisplay(); break;
        case 'd': xCubo[selected] += 0.1; glutPostRedisplay(); break;
    	case '1': selected = 0; break;
    	case '2': selected = 1; break;
    }
}







void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
                2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
                2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void
main(int argc, char **argv)
{
    glutInit(&argc, argv);

/* need both double buffering and z buffer */

    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    //glutIdleFunc(spinCube); //callback quando não estou fazer nada faz neste caso a rotação
    glutMouseFunc(mouse);
    glutSpecialFunc(keyboard); // Registra a função de callback do teclado
    glutKeyboardFunc(keyboard2); // Registra a função de callback do teclado(teclado usado no Paint)
    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
    glutMainLoop();
}