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

// Variável de escala global
static GLfloat scale = 1.0;






void tempo()
{
    int i;
    double max = 2500000.0;
    for (i=0; i<max; i++)
        (1/max)*max*max*max/3.14 + (1/max)*max*max*max/3.14 + (1/max)*max*max*max/3.14 + (1/max)*max*max*max/3.14;

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

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

void display(void)
{
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();


    // Aplica a escala ao cubo
    glScalef(scale, scale, scale);

    // Aplica rotações ao cubo em torno dos eixos X, Y e Z
    glRotatef(theta[0], 1.0, 0.0, 0.0); // Rotação em torno do eixo X
    glRotatef(theta[1], 0.0, 1.0, 0.0); // Rotação em torno do eixo Y
    glRotatef(theta[2], 0.0, 0.0, 1.0); // Rotação em torno do eixo Z

    colorcube();


    glFlush();

    tempo();

    //glutSwapBuffers();
}



void keyboard(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT: //seta para a esquerda
            theta[1] -= 5.0;
        if (theta[1] < 0.0) theta[1] += 360.0;
        break;
        case GLUT_KEY_RIGHT: //seta para a direita
            theta[1] += 5.0;
        if (theta[1] > 360.0) theta[1] -= 360.0;
        break;
        case GLUT_KEY_UP: //seta para cima
            theta[0] -= 5.0;
        if (theta[0] < 0.0) theta[0] += 360.0;
        break;
        case GLUT_KEY_DOWN: //seta para baixo
            theta[0] += 5.0;
        if (theta[0] > 360.0) theta[0] -= 360.0;
        break;
        case '+': // tecla +
            scale += 0.1;
        break;
        case '-': // tecla -
            if (scale > 0.1) scale -= 0.1;
        break;
    }
    glutPostRedisplay();
}


void keyboard2(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a': // tecla A
            theta[1] -= 5.0;
        if (theta[1] < 0.0) theta[1] += 360.0;
        break;
        case 'd': // tecla D
            theta[1] += 5.0;
        if (theta[1] > 360.0) theta[1] -= 360.0;
        break;
        case 'w': // tecla W
            theta[0] -= 5.0;
        if (theta[0] < 0.0) theta[0] += 360.0;
        break;
        case 's': // tecla S
            theta[0] += 5.0;
        if (theta[0] > 360.0) theta[0] -= 360.0;
        break;
        case '+': // tecla +
            scale += 0.1;
        break;
        case '-': // tecla -
            if (scale > 0.1) scale -= 0.1;
        break;
    }
    glutPostRedisplay();
}

// Função que faz a rotação do cubo
void spinCube()
{

/* Idle callback, spin cube 2 degrees about selected axis */

    theta[axis] += 2.0;
    if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    /* display(); */
    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y)
{

/* mouse callback, selects an axis about which to rotate */

    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
    if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
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