#include <gl/glut.h>


#define _USE_MATH_DEFINES // enable the definition of M_PI
#include <math.h>

#include "vector3.h"

//        Name : Box()
// Description : Draw an arbitrary size box. p_x, p_y, and 
//               p_z are the height of the box. We'll use this is a 
//               common primitive.
//      Origin : The back corner is at 0, 0, 0, and the box 
//               is entirely in the positive octant.
//
void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z);


//        Name : Sphere()
// Description : Draw a sphere with arbitrary radius
//      Origin : The center is in 0, 0, 0
//
void Sphere(float radius, int n_lat, int n_lon);


//		Name : Torus()
//Description : Draw a torus with a defined outer radius, inner radius and texture map
//
void Torus(float out_radius, float int_radius, int tx);



