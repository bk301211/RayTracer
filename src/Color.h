#ifndef _COLOR_H
#define _COLOR_H

#include "math.h"
#include "Vect.h"
#include <iostream>

struct COLOR {
	
	float r;
	float g;
	float b;
	
	//float w;
		
	//Empty Constructor
	COLOR()
	: r(r), g(g), b(b)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	
	COLOR(const float r, const float g, const float b)
	: r(r), g(g), b(b)
	{
		
	}
	
	COLOR(const double r, const double g, const double b)
	: r(r), g(g), b(b)
	{
		
	}
	
	COLOR(const int r, const int g, const int b)
		: r(r/255.0), g(g/255.0), b(b/255.0)
	{
	}
	
	COLOR(Vect v)
	{
		r = v.getVectX();
		g = v.getVectY();
		b = v.getVectZ();
	}
	
	const COLOR& operator +=(const COLOR &rgb)
	{
		r += rgb.r;
		g += rgb.g;
		b += rgb.b;
		return *this;
	}
	COLOR operator +(COLOR rgb)
	{
		return COLOR(r+rgb.r, g+rgb.g, b+rgb.b);
	}
	COLOR operator -(COLOR rgb)
	{
		return COLOR(r-rgb.r, g-rgb.g, b-rgb.b);
	}
	
	COLOR operator *(COLOR rgb)
	{
		return COLOR(r*rgb.r, g*rgb.g, b*rgb.b);
	}
	
	COLOR operator *(double value)
	{
		return COLOR(r * value, g * value, b * value);
	}
	//Divide this color by a single value
	COLOR operator /(const double value)
	{
		return COLOR((float)(r / value), (float)(g / value), (float)(b / value));
	}
	
	friend ostream& operator<<(ostream& os, COLOR& color)  {
		return os<<"r: "<<color.r<<"g: "<<color.g<<"b: "<<color.b<<endl;
	}


};

	extern COLOR lightYellow;
	extern COLOR lightBlue;
	extern COLOR beige;
	extern COLOR pink;
	extern COLOR darkGray;
	extern COLOR green;
	extern COLOR blue;
	extern COLOR orange;
	extern COLOR black;
	extern COLOR white;


	extern COLOR yolkAmb;
	extern COLOR yolkDiff;
	extern COLOR yolkSpec;
	extern COLOR yolkBord;

	extern COLOR eggAmb;
	extern COLOR eggDiff;
	extern COLOR eggSpec;
	extern COLOR eggBord;

	extern COLOR pomAmb;
	extern COLOR pomDiff;
	extern COLOR pomSpec;
	extern COLOR pomBord;
	extern COLOR pomShadows;

	extern COLOR backPlaneDiff;
	extern COLOR backPlaneAmb;
	extern COLOR groundPlaneDiff;


#endif