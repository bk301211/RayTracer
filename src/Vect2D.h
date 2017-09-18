#ifndef _VECT2D_H
#define _VECT2D_H

#include "math.h"
#include <iostream>

using namespace std;

class Vect2d {
	
	
	public:
	double x, y;
	
	Vect2d () {
		x = 0;
		y = 0;

	}
	
	Vect2d (double i, double j) {
		x = i;
		y = j;
	}
	
	// method functions
	double getVectX() { return x; }
	double getVectY() { return y; }
	
	Vect2d vectAdd (Vect2d v) {
	    return Vect2d (x + v.getVectX(), y + v.getVectY());
	}
	
	Vect2d operator/(Vect2d v){
		return Vect2d(x/v.getVectX(), y/v.getVectY());
	}
	
	Vect2d operator/(float v){
		return Vect2d(x/v, y/v);
	}
	
	Vect2d operator*(double scalar) {
	    return Vect2d (x*scalar, y*scalar);
	}
	
	Vect2d operator- (Vect2d v) {
		return Vect2d (x - v.getVectX(), y - v.getVectY());
	}
	
	Vect2d operator+(Vect2d v) {
	    return Vect2d (x + v.getVectX(), y + v.getVectY());
	}
	friend ostream& operator<<(ostream& os, Vect2d v)  {
		return os<<"Vect x:"<<v.x<<" y:"<<v.y<<endl;
	}
};

#endif