#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "math.h"
#include "Material.h"
#include "Color.h"
#include "Vect.h"
#include "Vect2D.h"
#include <iostream>
#include <stdint.h>
#include "EasyBMP/EasyBMP.h"
//#include "tinyOBJ/tiny_obj_loader.h"

using namespace std;

struct Intersection{
	float ti;
	Vect nH;
	Vect pH;
	
	
	Intersection(const float ti, const Vect nH, const Vect pH)
	: ti(ti), nH(nH), pH(pH)
	{}
	
	Intersection(const float ti, const Vect nH)
	: ti(ti), nH(nH), pH(Vect())
	{}
	
	Intersection(const float ti)
	: ti(ti), nH(Vect()), pH(Vect())
	{}
	Intersection()
	: ti(0), nH(Vect()), pH(Vect())
	{}
};
float glass  = 1.5;
float water = 1.3;

class Object{
	public:
	COLOR color;
	COLOR Ca;
	COLOR Cd;
	COLOR Cs;
	COLOR Cb;
	float reflection, transparency, ior;
	virtual Intersection intersect(Vect O, Vect nO){};
	virtual Vect GetSurfaceNormal(Vect hitPoint){};
	virtual float GetBorderIntensity(Vect nH, Vect npe){};
	virtual COLOR GetTextureColor(Vect UV){};
	virtual Vect GetNormalMap(Vect pH, Vect nH){};
	virtual COLOR GetSolidTexture(Vect pH){};
	virtual COLOR GetProjectedTexture(Vect pH){};
	virtual COLOR Get3DFunction(Vect pH){};
	virtual COLOR GetTextureCombined(Vect pH){};
	virtual COLOR GetReflection(Vect pH){};
	string filename;
	Vect p0, p1, p2;
	Vect2d UV1;
	//int TEXtype;
	int NORM;
	
};

struct SceneDefinition(){
	
}

//plane
class Plane:public Object{
	public:
	Vect normal;
	Vect Pc;
	float reflection, transparency, ior;
	
	Vect n0;
	Vect n1;
	float s0;
	float s1;
	BMP texture;
	BMP normalMap;
	int TEXtype;
	int NORM;


	Plane(){
		normal = Vect(1, 0, 0).normalize();
		Pc = Vect(100, 0, 0);
		reflection = 0;
		transparency = 0;
		ior = 0;
		
		color = darkGray;
		Ca = black;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		TEXtype = 0;
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	
	Plane(Vect n, Vect cen, COLOR col){
		normal = n.normalize();
		Pc = cen;
		reflection = 0;
		transparency = 0;
		
		color = col;
		Ca = black;
		Cd = col;
		Cs = white;
		Cb = green;
		
		TEXtype = 0;
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	
	Plane(Vect n, Vect cen, COLOR col, float refl, float trans){
		normal = n.normalize();
		Pc = cen;
		reflection = refl;
		transparency = trans;
		ior = glass;
		
		color = col;
		Ca = black;
		Cd = col;
		Cs = white;
		Cb = green;
		
		TEXtype = 0;
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	
	Plane(Vect n, Vect cen, const char* tex, int t){
		normal = n.normalize();
		Pc = cen;
		reflection = 0;
		transparency = 0;
		ior = 0;
		
		texture.ReadFromFile(tex);
		color = darkGray;
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		NORM = 0;
		TEXtype = t;
		
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	Plane(Vect n, Vect cen, const char* tex, int t, float refl, float trans){
		normal = n.normalize();
		Pc = cen;
		reflection = refl;
		transparency = trans;
		ior = glass;
		
		texture.ReadFromFile(tex);
		color = darkGray;
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		NORM = 0;
		TEXtype = t;
		
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	Plane(Vect n, Vect cen, const char* tex, const char* norm, int t, float refl, float trans){
		normal = n.normalize();
		Pc = cen;
		reflection = refl;
		transparency = trans;
		ior = glass;
		
		texture.ReadFromFile(tex);
		normalMap.ReadFromFile(norm);
		color = darkGray;
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		
		NORM = 1;
		TEXtype = t;
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	
		Plane(Vect n, Vect cen, const char* tex, const char* norm, int t){
		normal = n.normalize();
		Pc = cen;
		reflection = 0;
		transparency = 0;
		ior = glass;
		
		texture.ReadFromFile(tex);
		normalMap.ReadFromFile(norm);
		color = darkGray;
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		
		NORM = 1;
		TEXtype = t;
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	}
	
	
	Plane(Vect n, Vect cen, COLOR col, COLOR a, COLOR d, COLOR s, COLOR b){
		normal = n.normalize();
		Pc = cen;
		reflection = 0;
		transparency = 0;
		ior = 0;
		
		color = col;
		Ca = a;
		Cd = d;
		Cs = s;
		Cb = b;
		
		n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
		n1 = normal.normalize().crossProduct(n0).normalize();
	
	}
	
	
	
	Vect GetSurfaceNormal(Vect hitPoint){
		return normal;
	}
	
	float GetBorderIntensity(Vect nH, Vect npe){
		return 0;
	}

	
	Intersection intersect(Vect rayOrigin, Vect rayDirection){
		Vect rayVect = Pc - rayOrigin;
		float a = normal.dotProduct(rayDirection);
		if (a >= 0) {
			return Intersection(0);
		}
		else{
			Intersection intersection;
			intersection.ti = normal.dotProduct(rayVect) / a;
			intersection.nH = normal;
			intersection.pH = rayOrigin + (rayDirection * intersection.ti);
			return intersection;
		}
		
	}
	
	Vect GetNormalMap(Vect pH, Vect nH){
		
		if(NORM == 0) return nH;
		else{
			float normalIntensity = .9;
			s0 = 50;
			s1 = 50;
			
			float U = abs((pH - Pc).dotProduct(n0) / s0);
			float V = abs((pH - Pc).dotProduct(n1) / s1);
			
			U -= trunc(U); //clips off the whole number, so 1.2 will become .2
			V -= trunc(V);
			
			int i = U * normalMap.TellWidth();
			int j = V * normalMap.TellHeight();
			
			RGBApixel pixel = normalMap.GetPixel( i,j);
			/*
			float r = 2*(pixel.Red/255)-1;
			float g = 2*(pixel.Green/255)-1;
			float b = 2*(pixel.Blue/255)-1;
			*/
			/*
			float r = (2*pixel.Red-1)/255;
			float g = (2*pixel.Green-1)/255;
			float b = (2*pixel.Blue-1)/255;
			*/
			float r = 2*pixel.Red-1;
			float g = 2*pixel.Green-1;
			float b = 2*pixel.Blue-1;
			
			return (nH + (Vect(r, g, b) * normalIntensity)).normalize();
		}
	}
	
	COLOR GetTextureCombined(Vect pH){
		//2D Color
		if(TEXtype == 0){
			return Cd;
		}
		if(TEXtype == 1){
			s0 = 100;
			s1 = 100;
			
			float U = abs((pH - Pc).dotProduct(n0) / s0);
			float V = abs((pH - Pc).dotProduct(n1) / s1);
			
			U -= trunc(U); //clips off the whole number, so 1.2 will become .2
			V -= trunc(V);
			
			int i = U * texture.TellWidth();
			int j = V * texture.TellHeight();
			
			RGBApixel pixel = texture.GetPixel( i,j);

			return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		}
		//3D Solid
		if(TEXtype == 2){
			Vect surfNorm = pH - Pc;
			float scale = 20.0;
			
			
			double x = abs((n0/scale).dotProduct(pH - Pc));
			double y = abs((n1/scale).dotProduct(pH - Pc));
			
			
			float u = x - (int)x;
			if(x < 0) u = 1-u;
			float v = y - (int)y;
			if(y < 0) v = 1-v;
			
			int i = u * texture.TellWidth();
			int j = v * texture.TellHeight();
			
			RGBApixel pixel = texture.GetPixel( i,j);

			return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		}
		//3D Projected
		if(TEXtype == 3){
			Vect pL = Vect(0, 0, 0);
			Vect n2L = Vect(0, 0, 1).normalize();
			float d = 15.0;
			
			
			Vect surfNorm = pH - pL;
			float scale = 5;
			float determinate = n2L.dotProduct(surfNorm);
			
			
			double x = (n0/scale).dotProduct(((surfNorm/determinate)*d)- pL - n2L*d);
			double y = (n1/scale).dotProduct(((surfNorm/determinate)*d)- pL - n2L*d);
			
			
			float u = (x + 1)/2;
			//if(x < 0) u = 1-u;
			float v = (y + 1)/2;
			//if(y < 0) v = 1-v;
			
			int i = u * texture.TellWidth();
			int j = v * texture.TellHeight();
			
			RGBApixel pixel = texture.GetPixel( i,j);

			return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		}
		//3D Function
		if(TEXtype == 4){
			Vect zero = Vect(0, 0, 0);	
			Vect surfNorm = pH - Pc;
			float scale = 20;
			COLOR color;
			
			double x = (n0/scale).dotProduct(surfNorm);
			double y = (n1/scale).dotProduct(surfNorm);
			
			double Func3d = sin(10*x)*cos(10*y)/.5;
			
			if(y < Func3d)
				color = pink;
			else
				color = lightYellow;

			return color;
		}
	
	}
			
};


//sphere
class Sphere:public Object{
	public:
	Vect Pc;
	float rad;
	int TEXtype;
	int NORM;
	int motionblur;
	
	
	Vect n0;
	Vect n1;
	Vect n2;
	BMP texture;
	BMP normalMap;
	
	Sphere(){
		Pc = Vect(0, -5, 60);
		rad = 10;
		reflection = 0;
		transparency = 0;
		
		color = darkGray;
		Ca = black;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		motionblur = 0;
		TEXtype = 0;
	}
	
	Sphere(Vect cen, float r, COLOR col){
		Pc = cen;
		rad = r;
		reflection = 0;
		transparency = 0;
		
		color = col;
		Ca = darkGray;
		Cd = col;
		Cs = white;
		Cb = green;
		TEXtype = 0;
		motionblur = 0;
	}
	Sphere(Vect cen, float r, COLOR col, int MB){
		Pc = cen;
		rad = r;
		reflection = 0;
		transparency = 0;
		
		color = col;
		Ca = darkGray;
		Cd = col;
		Cs = white;
		Cb = green;
		TEXtype = 0;
		motionblur = 1;
	}
	
	Sphere(Vect cen, float r, COLOR col, float refl, float trans){
		Pc = cen;
		rad = r;
		reflection = refl;
		transparency = trans;
		ior = glass;
		
		color = col;
		Ca = darkGray;
		Cd = col;
		Cs = white;
		Cb = green;
		TEXtype = 0;
		motionblur = 0;
	}
	
	Sphere(Vect cen, float r, const char* tex, int t){
		Pc = cen;
		rad = r;
		reflection = 0;
		transparency = 0;
		ior = glass;
		
		texture.ReadFromFile(tex);
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		TEXtype = t;
		NORM = 0;
		motionblur = 0;
		
		n0 = Vect(0,1,0);
		n1 = Vect(1,0,0);
		n2 = Vect(0,0,1);
		
	}
	
	Sphere(Vect cen, float r, const char* tex, const char* norm, int t, float refl, float trans){
		Pc = cen;
		rad = r;
		reflection = refl;
		transparency = trans;
		ior = glass;
		
		texture.ReadFromFile(tex);
		normalMap.ReadFromFile(norm);
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		TEXtype = t;
		NORM = 1;
		motionblur = 0;
		
		n0 = Vect(0,0,1);
		n1 = Vect(1,0,0);
		n2 = Vect(0,1,0);
		
	}
		
	Sphere(Vect cen, float r, const char* tex, const char* norm, int t){
		Pc = cen;
		rad = r;
		reflection = 0;
		transparency = 0;
		
		texture.ReadFromFile(tex);
		normalMap.ReadFromFile(norm);
		Ca = darkGray;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		TEXtype = t;
		NORM = 1;
		motionblur = 0;
		
		n0 = Vect(0,0,1);
		n1 = Vect(1,0,0);
		n2 = Vect(0,1,0);
		
	}
	
	Sphere(Vect cen, float r, COLOR col, COLOR a, COLOR d, COLOR s, COLOR b){
		Pc = cen;
		rad = r;
		color = col;
		Ca = a;
		Cd = d;
		Cs = s;
		Cb = b;
		motionblur = 0;
		
	}
	
	Vect GetSurfaceNormal(Vect hitPoint){
		
		return ((hitPoint - Pc)/rad).normalize();
	}
	
	float GetBorderIntensity(Vect nH, Vect npe){
		float b = 1 - abs(npe.dotProduct(nH));
		b = b<0.7?0.0:b;
		b = b>1.0?1.0:b;
		
		return b;
	}
	
	Vect GetNormalMap(Vect pH, Vect nH){
		
		if(NORM == 0) return nH;
		else{
			Vect surfNorm = pH - Pc;
			float normalIntensity = .2;
			
			double X = (n0.dotProduct(surfNorm))/rad;
			double Y = (n1.dotProduct(surfNorm))/rad;
			double Z = (n2.dotProduct(surfNorm))/rad;
			//cout<<"X: "<<X<<endl;
			//cout<<"n0: "<<n0<<endl;
			double phi = acos(Z);
			double dumb = Y/sin(phi);
			dumb = dumb<=-0.9999?-0.9999:dumb;
			dumb = dumb>=0.9999?0.9999:dumb;
			double theta = acos(dumb);
			if(X<0)
				theta = M_PI*2 - theta;
			//cout<<"u: "<<theta<<endl;
			//cout<<"y: "<<Y<<endl;
			//cout<<"phi: "<<phi<<endl;
			//cout<<"sin: "<<Y/sin(phi)<<endl;
			//cout<<"theta: "<<theta<<endl;
			//float U = abs((pH - Pc).dotProduct(n0) / s0);
			//float V = abs((pH - Pc).dotProduct(n1) / s1);
			
			//U -= trunc(U); //clips off the whole number, so 1.2 will become .2
			//V -= trunc(V);
			
			float u = theta/(M_PI*2);
			float v = phi/(M_PI*2);
			u = u<0.0?0.0:u;
			u = u>1.0?1.0:u;
			v = v<0.0?0.0:v;
			v = v>1.0?1.0:v;
			//cout<<"u: "<<u<<endl;
			//cout<<"v: "<<v<<endl;
			
			int i = u * normalMap.TellWidth();
			//cout<<"i: "<<i<<endl;
			int j = v * normalMap.TellHeight();
			//cout<<"j: "<<j<<endl;
			
			RGBApixel pixel = normalMap.GetPixel( i,j);
			/*
			float r = 2*(pixel.Red/255)-1;
			float g = 2*(pixel.Green/255)-1;
			float b = 2*(pixel.Blue/255)-1;
			*/
			
			float r = 2*pixel.Red-1;
			float g = 2*pixel.Green-1;
			float b = 2*pixel.Blue-1;
			
			
			//float r = pixel.Red;
			//float g = pixel.Green;
			//float b = pixel.Blue;
			
			return (nH + (Vect(r, g, b) * normalIntensity)).normalize();
		}
		
	}


//============================================================================================================================
//						Solid Texturing
//============================================================================================================================
	COLOR GetTextureCombined(Vect pH){
		//2D Color
		if(TEXtype == 0){
			return Cd;
		}
		if(TEXtype == 1){
			Vect surfNorm = pH - Pc;
			float scale = rad;
			
			
			double X = abs((n0.dotProduct(surfNorm))/scale);
			double Y = abs((n1.dotProduct(surfNorm))/scale);
			double Z = abs((n2.dotProduct(surfNorm))/scale);
			//cout<<"X: "<<X<<endl;
			//cout<<"n0: "<<n0<<endl;
			double phi = acos(Z);
			double dumb = Y/sin(phi);
			dumb = dumb<=-0.9999?-0.9999:dumb;
			dumb = dumb>=0.9999?0.9999:dumb;
			double theta = acos(dumb);
			if(X<0)
				theta = M_PI*2 - theta;
			
			//cout<<"theta: "<<theta<<endl;
			//float U = abs((pH - Pc).dotProduct(n0) / s0);
			//float V = abs((pH - Pc).dotProduct(n1) / s1);
			
			//U -= trunc(U); //clips off the whole number, so 1.2 will become .2
			//V -= trunc(V);
			
			float u = theta/(M_PI*2);
			float v = phi/(M_PI*2);
			//cout<<"u: "<<u<<endl;
			
			int i = u * texture.TellWidth();
			int j = v * texture.TellHeight();
			
			RGBApixel pixel = texture.GetPixel( i,j);
				
			return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		}
		
		//3D Solid
		if(TEXtype == 2){
			Vect O = Vect(0, 0, 0);
		
			Vect surfNorm = pH - O;
			float scale = rad;
			
			
			double x = abs((n0/scale).dotProduct(surfNorm));
			double y = abs((n1/scale).dotProduct(surfNorm));
			
			
			float u = x - (int)x;
			//if(x < 0) u = 1-u;
			float v = y - (int)y;
			//if(y < 0) v = 1-v;
			
			int i = u * texture.TellWidth();
			int j = v * texture.TellHeight();
			
			RGBApixel pixel = texture.GetPixel( i,j);

			return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		}
		
		//3D Projected
		if(TEXtype == 3){
			Vect pL = Vect(0, 0, 0);
			Vect n2L = Vect(0, 0, 1).normalize();
			float d = 15.0;
			
			
			Vect surfNorm = pH - pL;
			float scale = 5;
			float determinate = n2L.dotProduct(surfNorm);
			
			
			double x = (n0/scale).dotProduct(((surfNorm/determinate)*d)- pL - n2L*d);
			double y = (n1/scale).dotProduct(((surfNorm/determinate)*d)- pL - n2L*d);
			
			
			float u = (x + 1)/2;
			//if(x < 0) u = 1-u;
			float v = (y + 1)/2;
			//if(y < 0) v = 1-v;
			
			int i = u * texture.TellWidth();
			int j = v * texture.TellHeight();
			
			RGBApixel pixel = texture.GetPixel( i,j);
			
			return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		}
		
		//3D Function
		if(TEXtype == 4){
			Vect zero = Vect(0, 0, 0);	
			Vect surfNorm = pH - Pc;
			float scale = rad;
			COLOR color;
			
			double x = (n0/scale).dotProduct(surfNorm);
			double y = (n1/scale).dotProduct(surfNorm);
			
			double Func3d = sin(10*x)*cos(10*y)/.5;
			
			if(y < Func3d)
				color = blue;
			else
				color = white;

			return color;
		}
	
	}
		
	
	Intersection intersect(Vect rayOrigin, Vect rayDirection){
		
		float radiusSquared = rad*rad;
		float randY = 1;
		Vect newPc;
		if(motionblur == 1){ 
			randY = ((float)rand()/RAND_MAX);
			newPc = Vect(Pc.getVectX(), Pc.getVectY()*randY, Pc.getVectZ());
			
		}
		else {newPc = Pc;}
        Vect L = newPc - rayOrigin; 
		//Vect L = Pc - rayOrigin;
        float tca = L.dotProduct(rayDirection); 
		
        // if (tca < 0) return false;
        float d2 = L.dotProduct(L) - tca * tca; 
        if (d2 > radiusSquared) 
			return 0; 
		
        float thc = sqrt(radiusSquared - d2); 
        float t0 = tca - thc; 
        float t1 = tca + thc; 
		
		if (t0 > t1) std::swap(t0, t1); 
 
        if (t0 < 0) { 
            t0 = t1; // if t0 is negative, let's use t1 instead 
            if (t0 < 0) return Intersection(0); // both t0 and t1 are negative 
        } 
		
		Intersection intersection;
		intersection.ti = t0;
		intersection.pH = rayOrigin + (rayDirection * t0);
		intersection.nH = ((intersection.pH - newPc)/rad).normalize();
		
		return intersection;
		
	}
		
};

class Triangle:public Object{
	public:
	Vect p0, p1,p2;
	Vect n, n0, n1, n2, n3;
	Vect2d UV1, UV2, UV3;
	
	Triangle();
	
	Triangle(Vect idxp0, Vect idxp1, Vect idxp2, COLOR c, Vect2d uv1, Vect2d uv2, Vect2d uv3, Vect nm1, Vect nm2, Vect nm3){
	Cd = c;
	Ca = darkGray;
	Cs = white;
	p0 = idxp0;
	p1 = idxp1;
	p2 = idxp2;
	n0 = nm1;
	n1 = nm2;
	n2 = nm3;
	UV1 = uv1;
	}
	
	Triangle(Vect idxp0, Vect idxp1, Vect idxp2, COLOR c, Vect2d uv1, Vect2d uv2, Vect2d uv3){
	Cd = c;
	Ca = darkGray;
	Cs = white;
	p0 = idxp0;
	p1 = idxp1;
	p2 = idxp2;
	}
	
	Intersection intersect(Vect rayOrigin, Vect rayDirection){//Vect *verts;
		Vect pH;
		float ti;
		float u, v;
		int i = 0;
		//tinyobj::index_t idx = 0;
		//tinyobj::attrib_t attrib;
		
		
		//attrib[]
		//cout<<"Here1"<<endl;
		/*cout<<"attrib"<<attrib.vertices[i]<<endl;
		p0 = Vect(attrib.vertices[i],attrib.vertices[i+1],attrib.vertices[i+2]);
		cout<<"Here2"<<endl;
		p1 = Vect(attrib.vertices[i+3], attrib.vertices[i+4], attrib.vertices[i+5]);
		p2 = Vect(attrib.vertices[i+6], attrib.vertices[i+7], attrib.vertices[i+8]);
		*/
		//compute plane of triangle normal
		//Vect A  = (p1-p0).crossProduct(p2-p0);
		//Vect n = A.normalize();
		Vect n = (n0+n1+n2)/3;
		n = n*(-1);
		float area = n.magnitude()/2;
		
		Vect rayVect = p0 - rayOrigin;
		float a = n.dotProduct(rayDirection); //NdotDir
		float D = n.dotProduct(p0);
		
		//cout<<"a: "<<a<<endl;
		if (a >= 0) return Intersection(0);
		
		else{
		
			ti = fabs(-(n.dotProduct(rayOrigin)+D)/ a);
			//cout<<ti<<endl;
			
			if(ti<0) return Intersection(0);//return ti;
			//cout<<"here"<<endl;
			pH = rayOrigin + (rayDirection*ti);
			
			Vect C;
			
			Vect edge0 = p1-p0;
			//Vect edge0 = p0-p1;
			Vect vp0 = pH - p0;
			C = edge0.crossProduct(vp0);
			//C = vp0.crossProduct(edge0);
			if(rayDirection.dotProduct(C)<0) return Intersection(0);
			
			Vect edge1 = p2-p1;
			//Vect edge1 = p1-p2;
			Vect vp1 = pH - p1;
			C = edge1.crossProduct(vp1);
			//C = vp1.crossProduct(edge1);
			u = (C.magnitude()/2) / area;
			if(rayDirection.dotProduct(C)<0) return Intersection(0);
			
			Vect edge2 = p0-p2;
			//Vect edge2 = p2-p0;
			Vect vp2 = pH - p2;
			C = edge2.crossProduct(vp2);
			//C = vp2.crossProduct(edge2);
			v = (C.magnitude()/2) / area;
			if(rayDirection.dotProduct(C)<0) return Intersection(0);
			//cout<<ti<<endl;
			
			
			Intersection intersection;
			intersection.ti = ti;
			intersection.nH = n;
			intersection.pH = pH;
			return intersection;
			
		}

	}
	
	Vect GetSurfaceNormal(Vect hitPoint){
		
		cout<<"Here"<<endl;
		Vect A  = (p1-p0).crossProduct(p2-p0);
		Vect n = A.normalize();
		
		return n;
	}
	
	
};


class OBJ:public Object{
	public:
	vector<Vect> verticies;
	vector<Vect2d> uvs;
	vector<Triangle> tris;
	OBJ(string, COLOR);
	
	Intersection intersect(Vect pH, Vect nH){
		Intersection intersection;
		Intersection intersectionMin;
		intersectionMin.ti = INT_MAX;
        int inthold;
		
		for (int i = 0; i < tris.size(); i++)
		{
			intersection = tris[i].intersect(pH, nH);
			
			{
			  if(intersection.ti > 0 && intersection.ti < intersectionMin.ti)
			   intersectionMin = intersection;
			
			   inthold = i;
			   UV1 = tris[i].UV3;
			   
			  // c//out<<i<<endl;
			  
			  /*
			  if(  ti > 0 && ti < tMin){
			tMin = ti;
			illum = ILLUMINATION? shade(ti, cam.Pe, npe, object) : white;
			pixelColor = illum; 
			*/
			}

		}
		if(intersectionMin.ti != INT_MAX)
		{
			//n = tris[inthold].n;

			//cout<<max<<endl;
			return intersectionMin;
		}
		else{
			return Intersection(0);
		}
	}
		
	Vect GetSurfaceNormal(Vect hitPoint){
		
	}	
	Vect GetNormalMap(Vect pH, Vect nH){
		
		if(NORM == 0) return nH;
	}
};

OBJ::OBJ(string filename, COLOR col){
	int TempNumOne = filename.size();
	char path[100];
	Cd = col;
	Ca = darkGray;
	Cs = white;
	
	NORM = 0;
	
	for (int a = 0; a <= TempNumOne; a++)
	{
		path[a] = filename[a];
	}
	//Vars
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< Vect > temp_vertices;
	vector< Vect2d > temp_uvs;
	vector< Vect > temp_normals;
	bool hasNormals = false;
	//Read file
	FILE * file = fopen(path, "r");
	if (file == NULL){
		printf("Impossible to open the file !\n");
		//return vector<Vector3d>(0,0,0);
		exit;
	}
	
	//Read file until end
	int res;
	//cout << "Started reading " << filePath << "\n";
	while (res != EOF)
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		// else : parse lineHeader
		//Let\92s deal with the vertices first :
		if (strcmp(lineHeader, "v") == 0){
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			//cout << x << "\n";
			//cout << y << "\n";
			//cout << z << "\n\n";
			temp_vertices.push_back(Vect(x, y, z));

		}
		//If the first word of the line is \93v\94, then the rest has to be 3 floats, so create a glm::vec3 out of them, and add it to the vector.
		else if (strcmp(lineHeader, "vt") == 0){
			float x, y;
			fscanf(file, "%f %f\n", &x, &y);
			temp_uvs.push_back(Vect2d(x, y));
		}
		//Normals
		else if (strcmp(lineHeader, "vn") == 0){
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			temp_normals.push_back(Vect(x, y, z));
			hasNormals = true;
		}
		//And now the \93f\94, which is more difficult
		else if (strcmp(lineHeader, "f") == 0){
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				break;
			}
			//tris.push_back(Triangle(temp_vertices[vertexIndex[0]], temp_vertices[vertexIndex[1]], temp_vertices[vertexIndex[0]], shade));
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

		}
	}
	vector<Vect> vertices = temp_vertices;
	for (int i = 0; i < vertexIndices.size(); i++)
	{

		Vect2d uv1 = temp_uvs[uvIndices[i] - 1];
		Vect nm1 = temp_normals[normalIndices[i] - 1];
		Vect v1 = vertices[vertexIndices[i++] - 1];

		Vect2d uv2 = temp_uvs[uvIndices[i] - 1];
		Vect nm2 = temp_normals[normalIndices[i] - 1];
		Vect v2 = vertices[vertexIndices[i++] - 1];

		Vect2d uv3 = temp_uvs[uvIndices[i] - 1];
		Vect nm3 = temp_normals[normalIndices[i] - 1];
		Vect v3 = vertices[vertexIndices[i] - 1];
//
		if (hasNormals)
		{
			//tris.push_back(Triangle(v1, v2, v3, col, uv1, uv2, uv3));
			
			tris.push_back(Triangle(v1, v2, v3, col, uv1, uv2, uv3, nm1, nm2, nm3));
			//tris.push_back(Triangle(v1, nm1, uv1, v2, nm2, uv2, v3, nm3, uv3));
		}
		else
		{
			tris.push_back(Triangle(v1, v2, v3, col, uv1, uv2, uv3));
		}
	}
	cout << "Finished reading " << filename << "\n";
	fclose(file);
};	
	
	
	
	//Vect p0;
	//Vect p1;
	//Vect p2;
	
	//tinyobj::attrib_t attrib;
	//vector<tinyobj::shape_t> shapes;
	//vector<tinyobj::material_t> materials;
	
	
	/*
	COLOR color;
	COLOR Ca;
	COLOR Cd;
	COLOR Cs;
	COLOR Cb;
	virtual float intersect(Vect O, Vect nO){};
	virtual Vect GetSurfaceNormal(Vect hitPoint){};
	virtual float GetBorderIntensity(Vect nH, Vect npe){};
	virtual COLOR GetTextureColor(Vect UV){};
	virtual Vect GetNormalMap(Vect pH, Vect nH){};
	virtual COLOR GetSolidTexture(Vect pH){};
	virtual COLOR GetProjectedTexture(Vect pH){};
	virtual COLOR Get3DFunction(Vect pH){};
	
	float intersect(Vect O, Vect nO){
		Vect rayVect = Pc - O;
		float a = normal.dotProduct(nO);
		if (a >= 0) return 0;
		else{
			return normal.dotProduct(rayVect) / a;
		}
		
	}
	
	*/

	/*OBJ(){
		p0 = Vect(1, 0, 20);
		p1 = Vect(3, 1, 20);
		p2 = Vect(2, 4, 20);

		color = white;
		Ca = white;
		Cd = darkGray;
		Cs = white;
		Cb = green;
		
		//bg = COLOR(0, 0, 0);
	}
	
	OBJ(const char* shape, COLOR color){//string, color
		
		//convert filepath to char *
	//int TempNumOne = filePath.size();
	//char path[100];
	//for (int a = 0; a <= TempNumOne; a++)
	//{
	//	path[a] = filePath[a];
	//}
	//Vars
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< Vect > temp_vertices;
	//vector< Vector2f > temp_uvs;
	vector< Vect > temp_normals;
	bool hasNormals = false;
	//Read file
	FILE * file = fopen(shape, "r");
	if (file == NULL){
		printf("Impossible to open the file !\n");
		return;
	}

	//Read file until end
	int res;
	//cout << "Started reading " << filePath << "\n";
	while (res != EOF){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		// else : parse lineHeader
		//Let’s deal with the vertices first :
		if (strcmp(lineHeader, "v") == 0){
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			//cout << x << "\n";
			//cout << y << "\n";
			//cout << z << "\n\n";
			temp_vertices.push_back(Vect(x, y, z));

		}
		//If the first word of the line is “v”, then the rest has to be 3 floats, so create a glm::vec3 out of them, and add it to the vector.
		/*else if (strcmp(lineHeader, "vt") == 0){
			float x, y;
			fscanf(file, "%f %f\n", &x, &y);
			temp_uvs.push_back(Vector2f(x, y));
		}*/
		//Normals
		/*else if (strcmp(lineHeader, "vn") == 0){
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			temp_normals.push_back(Vect(x, y, z));
			hasNormals = true;
		}

		//And now the “f”, which is more difficult
		else if (strcmp(lineHeader, "f") == 0){
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			//tris.push_back(Triangle(temp_vertices[vertexIndex[0]], temp_vertices[vertexIndex[1]], temp_vertices[vertexIndex[0]], 
			
			));
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			//uvIndices.push_back(uvIndex[0]);
			//uvIndices.push_back(uvIndex[1]);
			//uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	verticies = temp_vertices;
	//cout << "Finished reading " << filePath << "\n";
	fclose(file);

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		Vector2f uv1 = temp_uvs[uvIndices[i] - 1];
		Vector3f nm1 = temp_normals[normalIndices[i] - 1];
		Vector3f v1 = verticies[vertexIndices[i++] - 1];

		Vector2f uv2 = temp_uvs[uvIndices[i] - 1];
		Vector3f nm2 = temp_normals[normalIndices[i] - 1];
		Vector3f v2 = verticies[vertexIndices[i++] - 1];

		Vector2f uv3 = temp_uvs[uvIndices[i] - 1];
		Vector3f nm3 = temp_normals[normalIndices[i] - 1];
		Vector3f v3 = verticies[vertexIndices[i] - 1];

		if (hasNormals)
		{
			//tris.push_back(Triangle(v1, v2, v3, shade));
			tris.push_back(Triangle(v1, nm1, uv1, v2, nm2, uv2, v3, nm3, uv3, shade));
		}
		else
		{
			tris.push_back(Triangle(v1, v2, v3, shade));
		}
	}
	
		color = white;
		Ca = white;
		Cd = darkGray;
		Cs = white;
		Cb = green;


		
		
		/*
		vector<Vect> vertices;
		vector<uint32_t> indices;
		
		string inOBJ = filename;
		tinyobj::attrib_t attrib;
		vector<tinyobj::shape_t> shapes;
		vector<tinyobj::material_t> materials;
		string err;
		tinyobj::index_t index;
	
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inOBJ.c_str());
		cout<<ret<<endl;
		
		for(size_t s = 0; s < shapes.size(); s++){
			for (size_t v = 0; v < attrib.vertices.size(); v++){
				Vect vertex;
				
				vertices.push_back(vertex);
				indices.push_back(indices.size());
				
				vertex = Vect(attrib.vertices[3*index.vertex_index+0], attrib.vertices[3*index.vertex_index+1], attrib.vertices[3*index.vertex_index+2] );
				cout<<"Vect.X"<<vertex.getVectX()<<endl;
				
			}
		}
		*/
		//p0, p1, p2 = what... Needs to be here!...?
		
		
		/*
		for(size_t s = 0; s < shapes.size(); s++){
			
			size_t index_offset = (size_t)0;
			
			for(size_t f = 0; f<shapes[s].mesh.num_face_vertices.size(); f++){
				int fv = shapes[s].mesh.num_face_vertices[f];
				
				for(size_t v = 0; v < fv; v++){
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset+v];
				
				}
				index_offset += fv;
				shapes[s].mesh.material_ids[f];
			}
			
		}	*/	
		//p0 = Vect(1, 0, 20);
		//p1 = Vect(3, 1, 20);
		//p2 = Vect(2, 4, 20);
		/*
		Vect p0 = verts[i];
		Vect p1 = verts[i+1];
		Vect p2 = verts[i+2];
		*/

		
		
		//bg = COLOR(0, 0, 0);
	
	/*
	float intersect(Vect O, Vect nO){//Vect *verts;
		Vect pH;
		float ti;
		float u, v;
		int i = 0;
		//tinyobj::index_t idx = 0;
		//tinyobj::attrib_t attrib;
		
		
		//attrib[]
		/*cout<<"Here1"<<endl;
		cout<<"attrib"<<attrib.vertices[i]<<endl;
		p0 = Vect(attrib.vertices[i],attrib.vertices[i+1],attrib.vertices[i+2]);
		cout<<"Here2"<<endl;
		p1 = Vect(attrib.vertices[i+3], attrib.vertices[i+4], attrib.vertices[i+5]);
		p2 = Vect(attrib.vertices[i+6], attrib.vertices[i+7], attrib.vertices[i+8]);
		
		//compute plane of triangle normal
		Vect A  = (p1-p0).crossProduct(p2-p0);
		Vect n = A.normalize();
		float area = n.magnitude()/2;
		
		Vect rayVect = p0 - O;
		float a = -n.dotProduct(nO); //NdotDir
		float D = n.dotProduct(p0);
		
		//cout<<"a: "<<a<<endl;
		if (a >= 0) return 0;
		
		else{
			/*
			ti = -(n.dotProduct(O)+D)/ a;
			
			//if(ti<0) return 0;//return ti;
			//cout<<"here"<<endl;
			pH = O + (nO*ti);
			
			Vect C;
			
			Vect edge0 = p1-p0;
			Vect vp0 = pH - p0;
			C = edge0.crossProduct(vp0);
			if(nO.dotProduct(C)<0) return 0;
			
			Vect edge1 = p2-p1;
			Vect vp1 = pH - p1;
			C = edge1.crossProduct(vp1);
			if(nO.dotProduct(C)<0) return 0;
			
			Vect edge2 = p0-p2;
			Vect vp2 = pH - p2;
			C = edge2.crossProduct(vp2);
			if(nO.dotProduct(C)<0) return 0;
			
			return ti;
			*/
			/*
			ti = -(n.dotProduct(O)+D)/ a;
			
			//if(ti<0) return 0;//return ti;
			//cout<<"here"<<endl;
			pH = O + (nO*ti);
			
			Vect C;
			
			Vect edge0 = p1-p0;
			Vect vp0 = pH - p0;
			C = edge0.crossProduct(vp0);
			if(nO.dotProduct(C)<0) return 0;
			
			Vect edge1 = p2-p1;
			Vect vp1 = pH - p1;
			C = edge1.crossProduct(vp1);
			u = (C.magnitude()/2) / area;
			if(nO.dotProduct(C)<0) return 0;
			
			Vect edge2 = p0-p2;
			Vect vp2 = pH - p2;
			C = edge2.crossProduct(vp2);
			v = (C.magnitude()/2) / area;
			if(nO.dotProduct(C)<0) return 0;
			
			return ti;
			//Vect A0 = (pH-p1).crossProduct(pH-p2);
			//Vect A1 = (pH-p2).crossProduct(pH-p0);
			//Vect A2 = (pH-p0).crossProduct(pH-p1);
			
			//u = A1.magnitude()/A.magnitude();
			//cout<<"A1.x: "<<A1.x<<endl;
			//cout<<"u: "<<u<<endl;
			//v = A2.magnitude()/A.magnitude();
			/*
			float test = 1-u-v;
			if(u > 0 && u < 1 && v > 0 && v < 1 && test > 0 && test < 1){
				return ti;
			}
			*/
			
			//float X = n2.dotProduct(rayVect) / a;
			//cout<<"X: "<<X<<endl;
			//return -n2.dotProduct(rayVect) / a;
			
		//}
		
		//pH = O + (nO*ti);
		//Vect A  = (p1-p0).crossProduct(p2-p0);
		//Vect A0 = (pH-p1).crossProduct(pH-p2);
		//Vect A1 = (pH-p2).crossProduct(pH-p0);
		//Vect A2 = (pH-p0).crossProduct(pH-p1);
		
		///float u = 
		//float v = 
		
		
		//return ti;
	//}
	
	
//};


#endif