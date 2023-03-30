/***********************************************************
 * Lab session October 11th 2011
 *
 * Description: 
 * visualization of a cube
 *
 ***********************************************************/

#include <gl/glut.h>
#include <cstdio>

GLint FPS = 30;		// Frames per Second. used in the animation function
			// to control the maximum number of frames generated per second 

int spin_x = 0, old_x = 0;		// spin_ amount of spinning
int spin_y = 0, old_y = 0;		// old_  previous value
int phase = 0;		// specifies the current state of the animation

/*
 * menu function
 *
 * op - integer representing the chosen action
 */
void menu(int op) {

  switch(op) {
  case 'Q':
  case 'q':
    exit(0);
  }
}

/*
 * invoked by GLUT when a key is pressed
 *
 * key - pressed key
 * x, y - mouse coordinates
 */
void keyboardDown(unsigned char key, int x, int y) {

  switch(key) {
  case 'Q':
  case 'q':
  case  27:   // ESC
    exit(0);
  }
}

/*
 * invoked by GLUT when a key is released
 *
 * key - pressed key
 * x, y - mouse coordinates
 */
void keyboardUp(unsigned char key, int x, int y) {}

/*
 * invoked by GLUT when the window is modified
 * 
 * width. height - new size of the window
 */
void reshape(int width, int height) 
{
  GLfloat fieldOfView = 45.0f;
  glViewport (0, 0, (GLsizei) width, (GLsizei) height);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fieldOfView, (GLfloat) width/(GLfloat) height, 0.1, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 * invoked by GLUT when a mouse button is released or pressed
 *
 * button - identifier of the button
 * state - current state of the button
 * x, y - mouse coordinates
 */
void mouseClick(int button, int state, int x, int y) 
{
	old_x = x;
	old_y = y;

	glutPostRedisplay();

	printf("mouseClick function, button: %d, state: %d, x: %d, y: %d\n", button, state, x, y);
}

/*
 * invoked by GLUT when the mouse moves
 *
 * x, y - mouse coordinates
 *
 * 
 */
void mouseMotion(int x, int y) 
{
	spin_x = x - old_x;
	spin_y = y - old_y;

	glutPostRedisplay();

	printf("mouseMotion function, button: x: %d, y: %d\n", x, y);
}

/*
 * draws the axis
 *
 * length - length of the 3 axis
 */
void DrawAxes(float length)
{
	glPushMatrix();
	glScalef(length, length, length);

		glLineWidth(2.f);
		glBegin(GL_LINES);

		// x red
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(1.f, 0.f, 0.f);

		// y green
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 1.f, 0.f);

		// z blue
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 1.f);

		glEnd();
		glLineWidth(1.f);

	glPopMatrix();
}

/*
 * draws the scene
 */
void draw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(  2, 2, 2,		// eye position
				0, 0, 0,		// center
				0, 1, 0);		// vector UP

	glTranslatef(-3.f, -3.f, -3.f);
	DrawAxes(2.0);

	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	// insert here the code for the drawing of the scene
	glColor3f( .4f, .4f, .4f );
	glutSolidCube(2.f);
	
	glFlush();
	glutSwapBuffers();

	printf("draw function is called by GLUT\n");
}

/*
 * invoked when there are no other events to process
 */
void idle() { }

/*
 * initializes the state of OpenGL
 *
 * width, height - size of the OpenGL window
 */
void initGL(int width, int height) 
{
	// color and type of the lights	
	GLfloat light_ambient_0[] = {0.65, 0.65, 0.65, 1.0};// ambient color of light 0
	GLfloat light_diffuse_0[] = {1.0, 1.0, 1.0, 1.0};	// diffuse color of light 0
	GLfloat light_specular_0[] = {1.0, 1.0, 1.0, 1.0};	// specular color of light 0
	GLfloat light_position_0[] = {5.0, 5.0, 0.0, 0.0};	// position of light 0
	
	glLightfv (GL_LIGHT0, GL_AMBIENT,	light_ambient_0);
	glLightfv (GL_LIGHT0, GL_DIFFUSE,	light_diffuse_0);
	glLightfv (GL_LIGHT0, GL_SPECULAR,	light_specular_0);
	glLightfv (GL_LIGHT0, GL_POSITION,	light_position_0);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	reshape(width, height);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

/*
 * invoked each 1000/FPS milliseconds.
 * In this function you need to change the value of the parameters for next frame.
 * whenever the state changes, call glutPostRedisplay() to update the visualization.
 *
 * t - is the last parameter of the glutTimerFunc
 */
void animation(int t)
{
   switch (phase) {
      case 0: // standby state
         break;
      case 1: // first animation phase
		  glutPostRedisplay();
         break;
   }
   glutTimerFunc((int) 1000/FPS, animation, 0);

// The glutTimerFunc is an alarm that rings after x milliseconds. 
// If you need it to ring again, you need to invoke it again.
}

/*
 * initializes GLUT, registers the callback functions and starts the main loop
 *
 */
int main(int argc, char** argv) 
{
	int width = 800;
	int height = 600;
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Perspective's GLUT Template");
	
	// registra le callback
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);  
	glutIdleFunc(idle);
	glutTimerFunc((int) 1000/FPS, animation, 0);
	glutIgnoreKeyRepeat(false); // process keys held down
	
	// creates a submenu
	int subMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Do nothing", 0);
	glutAddMenuEntry("Really Quit", 'q');
	
	// creates the main menu (right button)
	glutCreateMenu(menu);
	glutAddSubMenu("Sub Menu", subMenu);
	glutAddMenuEntry("Quit", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	// initializes OpenGL
	initGL(width, height);
	
	// starts the main loop	
	glutMainLoop();
	return 0;
}