#include <gl/glut.h>

static GLfloat year=0.0f, day=0.0f;
void display();
void reshape(GLsizei , GLsizei );
void idle();
void keyboard(unsigned char , int, int);

void display()
{	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	//model view
	glColor3f(1.0, 1.0, 1.0);
	glutWireSphere(1.0, 20, 16);	// the Sun
	glPushMatrix();
		glRotatef(year, 0.0, 1.0, 0.0);
		glTranslatef(3.0, 0.0, 0.0);
		glRotatef(day, 0.0, 1.0, 0.0);
		glutWireSphere(0.5, 10, 8);	// the Planet
	glPopMatrix();
	// swap the front and back buffers
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{	// viewport transformation
	glViewport(0, 0, w, h);
	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 3.0, 5.0,	// eye
		      0.0, 0.0, 0.0,	// center
		      0.0, 1.0, 0.0);	// up
}

// GLUT idle function
void idle()
{
		day += 10.0;
		if(day > 360.0)
			day -= 360.0;
		year += 1.0;
		if(year > 360.0)
			year -= 360.0;
		// recall GL_display() function
		glutPostRedisplay();
}

// GLUT keyboard function
void keyboard(unsigned char key, int x, int y)
{	switch(key)
	{	case 'd':	day += 10.0;
			if(day > 360.0)		day -= 360.0;
			glutPostRedisplay();	break;
		case 'y':	year += 1.0;
			if(year > 360.0)		year -= 360.0;
			glutPostRedisplay();	break;
		case 'a':	// assign idle function
			glutIdleFunc(idle);	break;
		case 'A':	glutIdleFunc(0);		break;
		case 27:	exit(0);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Planet");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
