#ifndef _CAMERA_H
#define _CAMERA_H


#include "math.h"
#include "Vect.h"
#include <iostream>

using namespace std;

class Camera{
	public:
	Vect v2, vup, Pe, Porig;
	float d, s0, s1;
	Vect n0;
	Vect n2;
	Vect n1;
	int dofRays;
	Vect C; //convergence point
	float focalDist;
	
	Camera(){
			Camera(1);
		}
		
	Camera(float aspectRatio){
		//    "centered"
		//v2 = Vect(-.5 ,.1, 1);
		//v2 = Vect(.7, 0, .9);
		v2 = Vect(0, 0, .99);
		//    moves camera down and to the left
		//v2 = Vect(-.1, -.1, 1);
		//    moves camera up and to the right
		//v2 = Vect(.1, .1, 1);
		
		
		//    "level"
		vup = Vect(0, .8, 0);
		//    rotates counterclockwise
		//vup = Vect(.5, 1, 0);
		//    rotates clockwise
		//vup = Vect(-.5, 1, 0);
		//Pe = Vect(15, -1, 0);
		//Pe = Vect(-60, 0, 0);
		//Pe = Vect(0, 5, 0);
		
		Pe = Vect(0, 50, -20);
		
		d = 6;
		//closer field of view
		//float d = 20:
		//farther field of view
		//float d = 5;
		
		//float aspectRatio = (float)Ymax / (float)Xmax;
		
		s0=10.0;
		s1 = s0 * aspectRatio;
		
		n0 = vup.crossProduct(v2).normalize();
		
		//Vect n2 = v2.vectDiv((v2.normalize()));
		n2 = v2.normalize();
		//n1 = n2.crossProduct(n0);
		n1 = n2.crossProduct(n0).normalize();
		
		Vect Pc = Pe + (n2*d);

		Porig = Pc - (n0 * (s0/2))	- (n1*(s1/2));
		int dofRays = -1;
		/*Pc.Print("Pc");
		Porig.Print("Porig");
		v2.Print("v2");
		vup.Print("vup");
		n0.Print("n0");
		n2.Print("n2");
		n1.Print("n1");*/
		
		}
		
	Camera(Vect pos, Vect dir, float aspectRatio, int dof){
		
		v2 = dir;
		vup = Vect(0, .99, 0);
		dofRays = dof;
		Pe = pos;

		
		d = 5;
		//closer field of view
		//float d = 20:
		//farther field of view
		//float d = 5;
		
		//float aspectRatio = (float)Ymax / (float)Xmax;
		
		s0=10.0;
		s1 = s0 * aspectRatio;
		
		n0 = vup.crossProduct(v2).normalize();
		
		//Vect n2 = v2.vectDiv((v2.normalize()));
		n2 = v2.normalize();
		//n1 = n2.crossProduct(n0);
		n1 = n2.crossProduct(n0).normalize();
		
		Vect Pc = Pe + (n2*d);
		
		focalDist = (Vect(-10, 30, 150) - Pe).magnitude();
		
		C = Pe + (n2*focalDist);
		//Vect newPc = 
		
		Porig = Pc - (n0 * (s0/2))	- (n1*(s1/2));
		
		
		

		/*Pc.Print("Pc");
		Porig.Print("Porig");
		v2.Print("v2");
		vup.Print("vup");
		n0.Print("n0");
		n2.Print("n2");
		n1.Print("n1");*/
		
		}	
		
};


#endif