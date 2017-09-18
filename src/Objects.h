#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "math.h"
#include "Color.h"
#include "Vect.h"
#include <vector> 
#include "Vect2D.h"
#include "Material.h"
#include "Intersection.h"
#include <iostream>
#include <stdint.h>
#include "EasyBMP/EasyBMP.h"
//#include "tinyOBJ/tiny_obj_loader.h"

class Material;

class Object{
	public:
	virtual Intersection intersect(Vect O, Vect nO) = 0;
	virtual Vect GetSurfaceNormal(Vect hitPoint) = 0;
	virtual Vect2d GetUV(Vect pH) = 0;
	
	Object();

	Material *material;
	
};

//plane
class Plane:public Object{
	public:
	Vect normal;
	Vect Pc;
	
	Vect n0;
	Vect n1;
	float s0;
	float s1;
	


	Plane();
	
	Plane(Vect n, Vect cen);
	
	Vect GetSurfaceNormal(Vect hitPoint);
	
	float GetBorderIntensity(Vect nH, Vect npe);

	
	Intersection intersect(Vect rayOrigin, Vect rayDirection);
	
	Vect2d GetUV(Vect pH);
			
};


//sphere
class Sphere:public Object{
	public:
	
	Vect Pc;
	float rad;
	
	Vect n0;
	Vect n1;
	Vect n2;
	
	Sphere();
	
	Sphere(Vect cen, float r);
	
	Vect GetSurfaceNormal(Vect hitPoint);
	
	float GetBorderIntensity(Vect nH, Vect npe);
	
	Intersection intersect(Vect rayOrigin, Vect rayDirection);
	
	Vect2d GetUV(Vect pH);
		
};

class Triangle{
	public:
	
	Vect p0, p1,p2;
	Vect n, n0, n1, n2, n3;
	Vect2d UV1, UV2, UV3;
	
	Triangle();
	
	Triangle(Vect idxp0, Vect idxp1, Vect idxp2, Vect2d uv1, Vect2d uv2, Vect2d uv3, Vect nm1, Vect nm2, Vect nm3);
	
	Triangle(Vect idxp0, Vect idxp1, Vect idxp2, Vect2d uv1, Vect2d uv2, Vect2d uv3);
	
	Intersection intersect(Vect rayOrigin, Vect rayDirection);
	
	Vect GetSurfaceNormal(Vect hitPoint);
	Vect2d GetUV(Vect pH);
};

class OBJ:public Object{
	public:
	vector<Vect> verticies;
	vector<Vect2d> uvs;
	vector<Triangle> tris;
	
	OBJ(string filename, Vect position);
	
	Intersection intersect(Vect pH, Vect nH);
	Vect GetSurfaceNormal(Vect hitPoint);
	Vect2d GetUV(Vect pH);
};



#endif