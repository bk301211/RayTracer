#ifndef _VECT_H
#define _VECT_H

#include "math.h"
#include <iostream>

using namespace std;

class Vect {
	
	
	public:
	double x, y, z;
	
	Vect () {
		x = 0;
		y = 0;
		z = 0;
	}
	
	Vect (double i, double j, double k) {
		x = i;
		y = j;
		z = k;
	}
	
	// method functions
	double getVectX() { return x; }
	double getVectY() { return y; }
	double getVectZ() { return z; }

	double magnitude () {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	double magnitudeSquared () {
		return (x*x) + (y*y) + (z*z);
	}
	
	Vect normalize () {
		double magnitude = sqrt((x*x) + (y*y) + (z*z));
		return Vect (x/magnitude, y/magnitude, z/magnitude);
	}
		
	Vect negative () {
		return Vect (-x, -y, -z);
	}
			
	double dotProduct (Vect v) {

		return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
	}	
		
	Vect crossProduct (Vect v) {

		
		return Vect (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
	}
		
    Vect vectAdd (Vect v) {
	    return Vect (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
	}
	
	Vect vectMult(double scalar) {
	    return Vect (x*scalar, y*scalar, z*scalar);
	}

	Vect vectSub (Vect v) {
		return Vect (x - v.getVectX(), y - v.getVectY(), z - v.getVectZ());
	}
	Vect vectDiv (Vect v) {
		return Vect(x/v.getVectX(), y/v.getVectY(), z/v.getVectZ());
	}
	
	Vect operator/(Vect v){
		return Vect(x/v.getVectX(), y/v.getVectY(), z/v.getVectZ());
		
	}
	
	Vect operator/(float v){
		return Vect(x/v, y/v, z/v);
		
	}
	
	Vect operator*(double scalar) {
	    return Vect (x*scalar, y*scalar, z*scalar);
	}
	Vect operator- (Vect v) {
		return Vect (x - v.getVectX(), y - v.getVectY(), z - v.getVectZ());
	}
	
	Vect operator+(Vect v) {
	    return Vect (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
	}
	
	friend ostream& operator<<(ostream& os, Vect& v)  {
		return os<<"Vect x:"<<v.x<<" y:"<<v.y<<" z:"<<v.z<<endl;
	}
	
	void Print(){
		cout<<"Vect x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
	}
	void Print(string name){
		cout<<name<<" x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
	}
			
		 
};

#endif
