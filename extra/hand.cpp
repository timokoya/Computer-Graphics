/***********************************************************
 * Lab session October 25th 2013
 *
 * Description: 
 * Display the elements of a hand 
 *
 ***********************************************************/

#include <iostream>
#include <gl/glut.h>

GLint FPS = 30;		// Frames per Second. used in the animation function
			// to control the maximum number of frames generated per second 

int spin_x = 0, old_x = 0;		// spin_ amount of spinning
int spin_y = 0, old_y = 0;		// old_  previous value
int phase = 0;		// specifies the current state of the animation

GLfloat 
	p1 = 0.0, p2 = 0.0,				// Global variables for the thumb (thumb)
	i1 = 0.0, i2 = 0.0, i3 = 0.0;	// Global variables for the finger

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
void keyboardDown(unsigned char key, int x, int y) 
{
	
   switch (key) 
   {
	   case 'a':
		   i1 += 1.0;
		   glutPostRedisplay();
		   break;
	   case 'b':
		   i2 += 1.0;
		   glutPostRedisplay();
		   break;
	   case 'c':
		   i3 += 1.0;
		   glutPostRedisplay();
		   break;
	   case 'd':
		   p1 += 1.0;
		   glutPostRedisplay();
		   break;
	   case 'e':
		   p2 += 1.0;
		   glutPostRedisplay();
		   break;
       case '+':
		   FPS++;
		   break;
	   case '-':
		   if (FPS > 0) FPS--;
		   break;
	   case ' ':
		   spin_x += 5.0;
		   glutPostRedisplay();
		   break;      
	   case '.':
		   p1 = p2 = i1 = i2 = i3 = 0.0;
		   spin_x = 0.0;
		   glutPostRedisplay();
		   break;      
	   case 's':
		   p1 = p2 = i1 = i2 = i3 = 0.0;
		   phase = 1;
		   break;      
	   case 'Q':
	   case 'q':
	   case  27:   // ESC
		   exit(0);
		   break;
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
 * draws a palm of size dim*dim on the XY plane
 * and depth dim/4 along z
 */

void palm (float dim)
{
	glPushMatrix();
		glScalef(dim, dim, 0.25 * dim); 
		glutSolidCube(1.0);
	glPopMatrix();
}


/*
 * third phalanx of the finger [invoked by finger(...)]
 */
void phalanx3(float leng)
{
	glPushMatrix();
		glTranslatef(0.0, 0.15 * leng, 0.0);
		glScalef(0.66 * leng, leng, 0.66 * leng);
		glutSolidCube(0.2);	
	glPopMatrix();	
			
	// Sphere to round the end of the finger
	glPushMatrix();
		glTranslatef(0.0, 0.25*leng, 0.0);
		glutSolidSphere(0.075*leng, 10, 10);
	glPopMatrix();
}

/*
 * 	second phalanx of the finger [invoked by finger(...)]
 */
void phalanx2(float leng, float f)
{
	glPushMatrix();
		glTranslatef(0.0, 0.2 * leng, 0.0);
		glScalef(0.5 * leng, leng, 0.5 * leng);
		glutSolidCube(0.3);	
	glPopMatrix();

	// sphere	
	glPushMatrix();
		glTranslatef(0.0, 0.4 * leng, 0.0);
		glRotatef(f, 1.0, 0.0, 0.0);
		glutSolidSphere(0.075 * leng, 10, 10);
		phalanx3(leng);
	glPopMatrix();
}

/*
 * 	first phalanx of the finger [invoked by finger(...)]
 */
void phalanx1(float leng, float f1, float f2)
{
	// first phalanx
	glPushMatrix();
		glTranslatef(0.0, 0.2*leng, 0.0);
		glScalef(0.5*leng, leng, 0.5*leng);
		glutSolidCube(0.3);
	glPopMatrix();

	// sphere	
	glPushMatrix();
		glTranslatef(0.0,0.4*leng,0.0);
		glRotatef(f1, 1.0, 0.0, 0.0);
		glutSolidSphere(0.075*leng, 10,10);
		phalanx2(leng, f2);
	glPopMatrix();
}

/*
 * draws a finger with three joints. Small spheres are inserted between the phalanxes
 * and at the junction with the palm	
 *
 * leng -	length of the finger along the Y axis
 *			the dimensions on the XZ plane are proportional to leng
 * f1 -		rotation angle around the Z axis of the whole finger
 * f2 -		rotation angle around the Z axis of the second phalanx w.r.t. the first one
 * f3 -		rotation angle around the Z axis of the third phalanx w.r.t. the second one
 */
void finger(float leng, float f1, float f2, float f3)
{
	glPushMatrix();
		glRotatef(f1,1.0,0.0,0.0);
		glutSolidSphere(0.075*leng, 10,10);
		phalanx1(leng, f2, f3);
	glPopMatrix();
}

void phalanx_thumb2(float leng)
{
	glPushMatrix();
		glTranslatef(0.0, 0.2*leng, 0.0);
		glScalef(1.0*leng, leng, 1.0*leng);
		glutSolidCube(0.3);	
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.4*leng, 0.0);
		glutSolidSphere(0.2*leng, 10, 10);
	glPopMatrix();	
}

void phalanx_thumb1(float leng, float ang)
{
	// first phalanx
	glPushMatrix();
		glTranslatef(0.0, 0.3*leng, 0.0);
		glScalef(0.66*leng, leng, 0.66*leng);
		glutSolidCube(0.5);
	glPopMatrix();

	// second joint
	glPushMatrix();
		glTranslatef(0.0,0.6*leng,0.0);
		glRotatef(ang, 1.0, 0.0, 0.0);
		glutSolidSphere(0.2*leng, 10,10);
		phalanx_thumb2(leng);
	glPopMatrix();
}

/*
 * draws a thumb with a joint.
 * There are small spheres between the phalanxes and at the junction of the finger with the palm
 *
 * leng -	length of the thumb along the Y axis
 *			the dimensions on the XZ plane are proportional to leng
 * ang1 -	rotation angle of the whole thumb around the Z axis
 * ang2 -	rotation angle of the second phalanx with respect to the first one around the Z axis
 */
void thumb(float leng, float ang1, float ang2)
{
	glPushMatrix();
		glRotatef(ang1, 1.0,0.0,0.0);
		glutSolidSphere(0.2*leng, 10,10);
		phalanx_thumb1(leng, ang2);
	glPopMatrix();
}

void hand() //insert required parameters
{
   glPushMatrix();
 	glColor3f(1.0,1.0,1.0); // white palm
  	// insert transformations
   	// draws the palm
   glPopMatrix();

   glPushMatrix();
	glColor3f(1.0,0.0,0.0); // red thumb
  	// insert transformations
   	// draws the thumb
   glPopMatrix();

   glPushMatrix();
	glColor3f(0.0,1.0,0.0); // green index finger
  	// insert transformations
   	// draws the ndex finger
   glPopMatrix();

   glPushMatrix();
	glColor3f(0.0,0.0,1.0); // blue middle finger
  	// insert transformations
   	// draws the middle finger
   glPopMatrix();

   glPushMatrix();
	glColor3f(1.0,1.0,0.0); // yellow ring finger
  	// insert transformations
   	// draws the ring finger
   glPopMatrix();

   glPushMatrix();
	glColor3f(1.0,0.0,1.0); // light blue little finger
  	// insert transformations
   	// draws the little finger
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

	gluLookAt(  0.0, 1.0, 5.0,		// eye position
				0.0, 1.0, 0.0,		// center
				0.0, 1.0, 0.0);		// vector UP


//	glTranslatef(-3.f, -3.f, -3.f);
	DrawAxes(2.0);

	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	// insert here the code for the drawing of the scene

	//drawing of the palm
	glColor3f (0.1, 0.1, 1.0);
	palm(1.0);
	
	// drawing of the thumb on the left of the palm
	glColor3f (0.75, 0.1, 0.1);
	glPushMatrix();
		glTranslatef(-2.0,0.0,0.0);
		thumb(0.7, p1, p2);
	glPopMatrix();

	//drawing of the finger on the right of the palm
	glColor3f (0.1, 0.75, 0.1);
	glPushMatrix();
		glTranslatef(2.0,0.0,0.0);
		finger(1.0, i1, i2, i3);
	glPopMatrix();
	
	glutSwapBuffers();
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
	case 1: // opening phase of the index finger
			// insert commands to modify the values of the index finger
			// insert condition to change phase
		glutPostRedisplay();
		break;
	case 2: // opening phase of the middle finger
			// insert commands to modify the values of the middle finger
			// insert condition to change phase
		glutPostRedisplay();
		break;
	case 3: // opening phase of the ring finger
			// insert commands to modify the values of thel'ring finger
			// insert condition to change phase
		glutPostRedisplay();
		break;      
	case 4: // opening phase of the little finger
			// insert commands to modify the values of the little finger
			// insert condition to change phase
		glutPostRedisplay();
		break;      
	case 5: // opening phase of the thumb
			// insert commands to modify the values of the thumb
			// insert condition to change phase
		glutPostRedisplay();
		break;
	}
	glutTimerFunc((int) 1000/FPS, animation, 0);
// The glutTimerFunc is an alarm that rings after x milliseconds. 
// If you need it to ring again, you need to invoke it again.
}

/*
 * initializes GLUT, defines the callback functions, enters the main loop
 *
 * argc : number of command line parameters
 * argv : vector of the command line parameters
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
	
	// callback functions
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