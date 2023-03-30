// code for the verlet-based physical simulation

#ifndef __PARTICLE_SYSTEM__
#define __PARTICLE_SYSTEM__

#define TIME_STEP 0.01f
#define _USE_MATH_DEFINES 

#include "particle.h"
#include "colors.h"
#include <vector>
#include <math.h>

using namespace std;

class ParticleSystem 
{
	vector<Particle>   _particles;		// the particles

	Vector3     m_vGravity;				// gravity force applied to the particles system
	Vector3		m_force;
	float       m_fTimeStep;			// time step
	Vector3 attractor;
	int counter;

public:

	ParticleSystem()
	{
		m_vGravity = Vector3(0, -9.81f, 0);
		m_force = Vector3(5.8, 5.8, 5.8);
		m_fTimeStep = TIME_STEP;	
		attractor = Vector3(0, 0, 0);
		counter = 0;

	}

	void Reset()
	{
		_particles.clear();
	}

	// accessing the fields

	void SetGravity(Vector3 g)	{		m_vGravity = g;}

	void SetTimeStep(float ts)	{		m_fTimeStep = ts;}

	// adding a particle
	Particle* AddParticle(Particle _p)
	{
		_particles.push_back(_p);

		return &(_particles.back());
	}


	
	void drawCircle(float radius)
	{
		const float DEG2RAD = 3.14159/180;
	   glBegin(GL_LINE_LOOP);
 
	   for (int i=0; i <= 360; i++)
		   {
				float degInRad = i*DEG2RAD;
				glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
		   }
 
	  glEnd();
	}

	//void Build()																			//Build function for first point
	//{
	//	
	//	int n = 100;

	//	for (float i = -n; i <= n; i ++)
	//	{
	//		float b = rand();
	//		float a = rand();
	//		float c = rand();
	//		float x = 0;


	//		float v1 = -a/RAND_MAX * 10;
	//		float v2 = b/RAND_MAX * 20;
	//		float v3 = c/RAND_MAX * 10;
	//
	//		Vector3 pos(0,0,0);
	//		Particle p(pos);
	//		p.vel = Vector3(v1,v2,v3);
	//		//p.restPos = Vector3(0,v1,0);
	//		AddParticle(p);
	//	}
	//};  

		//void Build()																		//Build function for second point
		//{
		//										
		//	int n = 25;	
		//	float v1 = rand()/RAND_MAX * 10;
		//	float v2 = rand()/RAND_MAX * 20;
		//	float v3 = rand()/RAND_MAX * 10;

		//	for (int i = -n; i <= n; i++)
		//			{	
		//					for (int j = -n; j <= n; j++)
		//					{
		//						Vector3 pos(i, j, 0);
		//						Particle p(pos);
		//						p.vel = Vector3(v1,v2,v3);
		//						AddParticle(p);
		//					}
		//			}
		//};

	void Build()																						//Build function for third point
	{
		int n = 1000;																						//Number of particles

		for (int i = 0; i <= n; i++)
		{
			float a = 0, b = 0, c = 0;
			int max = 12, min = 8; 
			double maxa = M_PI/20, mina = - M_PI/20;

			double angle = 0; 

			angle = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (maxa-mina) + mina;

			a =	((rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (max-min) + min) * cos(angle);			//creates random values between 8 and 12 at an angle 
			b = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (max-min) + min * sin(angle);			//randomly picked between PI/20 and -PI/20
			//c = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (max-min) + min;
				
//			 printf("Values of a and b are %3.2f, %3.2f",a,b);
			Vector3 pos(0,0,0);
			Particle p(pos);
			p.vel = Vector3(-a, b ,0);
			AddParticle(p);
		}
		
	}
	void Update()
	{
				AccumulateForces();			// assigns the forces to the particles		
				vector<Particle>::iterator pIt;
				for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
				pIt->Update(m_fTimeStep);

				CollisionHandling();
	}

	// integration step
	//void Update()																										//Update function for second point
	//{
	//	
	//	if (counter < 300)
	//	{
	//			counter += 1;
	//			AccumulateForces();															// assigns the forces to the particles		
	//			vector<Particle>::iterator pIt;
	//			for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
	//			pIt->Update(m_fTimeStep);
	//			CollisionHandling();
	//			
	//			
	//			printf("First If statement %i " ,counter);									//Verifies the counter
	//	}
	//	if (counter == 300)
	//	{

	//					float x =0, y = 0, z = 0;											//declare and initialise random values

	//					int min = -5, max = 5;;

	//					x =	rand() % (max-min) + min;
	//					y = rand() % (max-min) + min;
	//					z = rand() % (max-min) + min;

	//					printf("Values of x y z are %3.2f, %3.2f, %3.2f :", x,y,z);
	//					attractor = Vector3(x,y,z);
	//					
	//					AccumulateForces();													// assigns the forces to the particles		
	//					vector<Particle>::iterator pIt;
	//					for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
	//					pIt->Update(m_fTimeStep);
	//					CollisionHandling();
	//					printf("second If statement");										//checking loop protocol
	//					counter = 0;
	//	}

	//	else
	//	{
	//		printf("oops");																	//checking loop protocol
	//	}
	//			
	//}	

	// draws the particles system
	// each particle is represented by a red point
	void Draw()
	{
		// draw round points
		glPointSize(4.f);
		glEnable(GL_POINT_SMOOTH);
		glAlphaFunc(GL_GREATER,0.5f); 
		glEnable(GL_ALPHA_TEST); 
		glEnable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		// draws the particles
		glBegin(GL_POINTS);

		glColor3f(1.f, 0.f, 0.f);
		vector<Particle>::iterator pIt;
		for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
		{
			Vector3& pos = pIt->pos;
			glVertex3f(pos.x, pos.y, pos.z);
		}

		glEnd();	

		glEnable(GL_LIGHTING);

		DrawCollisionPlaneYZ(3);
		DrawCollisionPlaneYZ(-3);
		DrawCollisionPlaneXZ(3);
		DrawSphere(Vector3(0, -6, 0), 6);
	}
	
private:

	// this function assigns all the forces applied to each particle
	//void AccumulateForces()
	//{
	//				
	//		// all the particles are influenced by gravity
	//		vector<Particle>::iterator pIt;
	//		for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
	//			{
	//				float L=(attractor-pIt->oldPos).Length();
	//				pIt->vel += (attractor - pIt->pos).Normalize();
	//				pIt->acc = m_force;
	//			}
	//}

	void AccumulateForces()
	{
		// all the particles are influenced by gravity
		vector<Particle>::iterator pIt;
		for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
		{
			pIt->acc = Vector3(0, 0, 0);
			pIt->acc += m_vGravity;
		}	
		
	}

	void CollisionHandling()
	{
		CollisionPlaneYZ(3);
		CollisionPlaneYZ(-3);
		CollisionPlaneXZ(3);

		CollisionSphere(Vector3(0, -6, 0), 6);
	}

	void CollisionPlaneYZ(float x)
	{
		vector<Particle>::iterator pIt;
		for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
		{
			if (((pIt->pos.x < x) && (x < 0)) || ((pIt->pos.x > x) && (x > 0)))
			{
				pIt->oldPos.x = pIt->pos.x;
				pIt->pos.x = x;
			}
		}
	}

	void DrawCollisionPlaneYZ(float x)
	{
		glLineWidth(5);
		glPushMatrix();
			glBegin(GL_LINES);
			glVertex3f(x, -x, 0);
			glVertex3f(x, x, 0);
			glEnd();
		glPopMatrix();
	}

	void CollisionPlaneXZ(float y)
	{
		vector<Particle>::iterator pIt;
		for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
		{
			if (((pIt->pos.y < y) && (y < 0)) || ((pIt->pos.y > y) && (y > 0)))
			{
				pIt->oldPos.y = pIt->pos.y;
				pIt->pos.y = y;
			}
		}
	}

	void DrawCollisionPlaneXZ(float y)
	{
		glPushMatrix();
		glLineWidth(5); 
		glBegin(GL_LINES);
		glVertex3f(-y, 0, 0);
		glVertex3f(-y, y, 0);
		glEnd();
		glPopMatrix();
	}

	void CollisionSphere(const Vector3 & c, float r)
	{
		
		vector<Particle>::iterator pIt;
		for(pIt = _particles.begin(); pIt != _particles.end(); pIt++) 
		{
			if (((pIt->pos.y < -1) && (c.y < 0)) || ((pIt->pos.z > 0) && (c.z > 0)))
			{
				pIt->oldPos.y = pIt->pos.y;
				pIt->pos.y = -1;
				pIt->oldPos.z = pIt->pos.z;
				pIt->pos.z= 0;
			}
		}
	}

	void DrawSphere(const Vector3 & c, float r)
	{
		glPushMatrix();

		glTranslatef(c.x, c.y, c.z);
		glutSolidSphere((double)r,30,30);
		glPopMatrix();

		glPushMatrix();
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex3f(c.y/2, r/2,0);
			glVertex3f(-c.y/2, r/2,0);
		glEnd();
		glPopMatrix();
	}
};

#endif // __PARTICLE_SYSTEM__