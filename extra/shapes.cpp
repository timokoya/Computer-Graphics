
#include "texture_manager.h"
#include "shapes.h"
#include "math.h"


void glVertex3(const Vector3 & v)
{
	glVertex3d(v.x, v.y, v.z);
}

void glNormal3(const Vector3 & v)
{
	glNormal3d(v.x, v.y, v.z);
}

void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z)
{
	// define the coordinates of the 8 vertices of the cube
   Vector3 a(0., 0., p_z);
   Vector3 b(p_x, 0., p_z);
   Vector3 c(p_x, p_y, p_z);
   Vector3 d(0., p_y, p_z);
   Vector3 e(0., 0., 0.);
   Vector3 f(p_x, 0., 0.);
   Vector3 g(p_x, p_y, 0.);
   Vector3 h(0., p_y, 0.);

   glPushMatrix();
   glEnable(GL_TEXTURE_2D); 

  	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // The magnification function ("linear" produces better results)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   TextureManager::Inst()->BindTexture(1);

   glTranslatef(p_x * -.5f, p_y * -.5, p_z * -.5);
 
   // Front
   glBegin(GL_QUADS);
      glNormal3d(0, 0, 1);
      glTexCoord2f(0, 1);
      glVertex3(a);
      glTexCoord2f(1, 1);
      glVertex3(b);
      glTexCoord2f(1, 0);
      glVertex3(c);
      glTexCoord2f(0, 0);
      glVertex3(d);
   glEnd();

   glDisable(GL_TEXTURE_2D);

   // Right
   glBegin(GL_QUADS);
      glNormal3d(1, 0, 0);
      glVertex3(c);
      glVertex3(b);
      glVertex3(f);
      glVertex3(g);
   glEnd();

   // Back
   glBegin(GL_QUADS);
      glNormal3d(0, 0, -1);
      glVertex3(h);
      glVertex3(g);
      glVertex3(f);
      glVertex3(e);
   glEnd();

   // Left
   glBegin(GL_QUADS);
      glNormal3d(-1, 0, 0);
      glVertex3(d);
      glVertex3(h);
      glVertex3(e);
      glVertex3(a);
   glEnd();

   // Top
   glBegin(GL_QUADS);
      glNormal3d(0, 1, 0);
      glVertex3(d);
      glVertex3(c);
      glVertex3(g);
      glVertex3(h);
   glEnd();

   // Bottom
   glBegin(GL_QUADS);
      glNormal3d(0, -1, 0);
      glVertex3(e);
      glVertex3(f);
      glVertex3(b);
      glVertex3(a);
   glEnd();

   glPopMatrix();

}

Vector3 SphereCoord(float i, float j, float n_lat, float n_lon)
{
	return Vector3(
		sin(M_PI * (i/n_lat)) * cos(2 * M_PI * (j/n_lon)), 
		sin(M_PI * (i/n_lat)) * sin(2 * M_PI * (j/n_lon)), 
		cos(M_PI * (i/n_lat)));
}

void Sphere(float radius, int n_lat, int n_lon)
{
	glEnable(GL_LIGHTING);

	glColor3f(1, 1, 1);
	// the sphere is made by quads, each quad is composed by two triangles
	glBegin(GL_TRIANGLES);
	for (float i = 0; i < n_lat; i += 1.f)
		for (float j = 0; j < n_lon; j += 1.f)
		{
			Vector3 p;

			// -- first triangle
			p = SphereCoord(i, j, n_lat, n_lon);
 	        glNormal3(p);
			glVertex3(p * radius);

			p = SphereCoord(i + 1, j, n_lat, n_lon);
			glNormal3(p);
			glVertex3(p * radius);

			p = SphereCoord(i + 1, j + 1, n_lat, n_lon);
			glNormal3(p);
			glVertex3(p * radius);


			// -- second triangle
			p = SphereCoord(i, j, n_lat, n_lon);
 	        glNormal3(p);
			glVertex3(p * radius);

			p = SphereCoord(i + 1, j + 1, n_lat, n_lon);
			glNormal3(p);
			glVertex3(p * radius);

			p = SphereCoord(i, j + 1, n_lat, n_lon);
			glNormal3(p);
			glVertex3(p * radius);

	}
	glEnd();
}

void Torus(float out_radius, float int_radius, int tx)
{

	glEnable(GL_LIGHTING);
    
	glPushMatrix();
	
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_SMOOTH);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // The magnification function ("linear" produces better results)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
		TextureManager::Inst()->BindTexture(tx);
    
	
		glColor3f(1, 1, 1);	
	
	
	
		int i, j, k;
		double s, t, x, y, z, twopi, u, v;
		int numc = 30, numt = 30;



		twopi = 2 * M_PI;
		for (i = 0; i < numc; i++)
		{
			 glBegin(GL_QUAD_STRIP);

		      for (j = 0; j <= numt; j++) 
				{
					for (k = 1; k >= 0; k--) 
						{
					
							s = (i + k) % numc + 0.5;
							t = j % numt;

							x = (out_radius + int_radius * cos(s * twopi /numc)) * cos(t * twopi /numt);
							y = (out_radius + int_radius * cos(s * twopi /numc)) * sin(t * twopi/numt);
							z = int_radius * sin(s * twopi / numc);

							//u = (i+k) / (float)numc;
							//v = j / (float)numt;
							
							v = (i+k) *(M_PI) / (float)numc;
							u = j* (M_PI) /(float)numt;


							glTexCoord2f(u, v);
							glVertex3f(x, y, z);
							
				}
		}
      glEnd();

   }
	  glPopMatrix();	

}

