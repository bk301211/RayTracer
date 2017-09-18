#ifdef __linux__ 
    //linux code goes here
#elif _WIN32
    #include <windows.h>
#else

#endif

#define TINYOBJLOADER_IMPLETMENTATION
#define MAX_RAY_DEPTH 3

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits.h>
#include <GL/glut.h>
#include <math.h>
#include "Vect.h"
#include "Lights.h"
#include "Camera.h"
#include "Scene.h"
#include "Color.h"
#include "Globals.h"
#include "Objects.h"

#include "Utility.h"
#include "RayTracer.h"
#include "Vect2D.h"
#include <typeinfo>
#include <algorithm>
#include "EasyBMP/EasyBMP.h"

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

int BORDER = 0;
int DIFFUSE = 1;
int SPECULAR = 1;
int ILLUMINATION = 1;
int AA = 6;
int DOF = 20;

int width = 1024;
int height = 640;

int tempX = -1;
int tempY = -1;

COLOR *pixels = new COLOR[width*height];

COLOR *diffuse = new COLOR[width*height];
COLOR *specular = new COLOR[width*height];
COLOR *reflection = new COLOR[width*height];

COLOR IntersectScene(COLOR pixelColor, Vect rayOrigin, Vect rayDirection, int rayDepth);

Scene scene;
Camera cam;


COLOR renderPixel(float x, float y, Camera cam){
		
	float focalDistance = 90;
	float radius = 4;
	
	if(cam.dofRays >  0){
		
		Vect Pp = cam.Porig + (cam.n0 * (x/width) * cam.s0) + (cam.n1 * (y/height) * cam.s1);
		COLOR pixelColor = black;
			
		Vect raydir = Pp - cam.Pe;
		raydir = raydir.normalize();
		Vect aimed = cam.Pe + (raydir * focalDistance);
		
		for(int i = 0; i < cam.dofRays; i++){
			
			float RX = (float)rand()/RAND_MAX*radius;
			float RY = (float)rand()/RAND_MAX*radius;
			
			Vect newPe;
			float camPeX = cam.Pe.getVectX();
			float camPeY = cam.Pe.getVectY();
			
			newPe = Vect(camPeX + RX, camPeY + RY, cam.Pe.getVectZ()); 
			
			Vect npe = (aimed - newPe).normalize();
			
			Intersection intersection = RayTracer::trace(&scene, newPe, npe, 0);
	
			if(intersection.ti > 0){
				
				pixelColor += intersection.object->material->shade(&scene, &intersection, newPe, npe, 0);
			}
		}
		return pixelColor / cam.dofRays;
	}
	else{
		
		Vect Pp = cam.Porig + (cam.n0 * (x/width) * cam.s0) + (cam.n1 * (y/height) * cam.s1);
		COLOR pixelColor = black;
		
		Vect raydir = Pp - cam.Pe;
		Vect aimed = cam.Pe + raydir*20;
		raydir = raydir.normalize();
		Vect npe = (Pp - cam.Pe).normalize();
		
		Intersection intersection = RayTracer::trace(&scene, Pp, npe, 0);
	
		if(intersection.ti > 0){
			pixelColor = intersection.object->material->shade(&scene, &intersection, Pp, npe, 0);
			return pixelColor;
		}
	}
		

	
	return black;
	

		
	

}

void render(Camera cam){
	pixels = new COLOR[width*height];
	int M = AA;
	int N = AA;

			
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int i = (y * width + x);
			

			
			float randomX = rand()/RAND_MAX;
			float randomY = rand()/RAND_MAX;
			
			float r = 0, g = 0, b = 0;
			
			COLOR pixelColor = black;
			
			
			for(int m = 0; m < M; m++){
				for(int n = 0; n < N; n++){
					
					double locX = x + (m/(double)M) + (randomX/(double)M);
					double locY = y + (n/(double)N) + (randomY/(double)N);
					
					pixelColor += renderPixel(locX,locY,cam);
				}
			}
			pixels[i] = pixelColor / (M*N);
				cout<< "Rendered:"<<x<<" : "<<y<<endl;
		}
	}

	
	cout<<"done"<<endl;
	glutPostRedisplay ();
}

void renderSingle(Camera cam, int x, int y){
	pixels = new COLOR[width*height];
	int i = (y * width + x);
	COLOR pixelColor = black;
	pixelColor += renderPixel(x,y,cam);
	pixels[i] = pixelColor;
	cout<<"done"<<endl;
	glutPostRedisplay ();
}


static void resize(int w, int h)
{   
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,(w/2),0,(h/2),0,1); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
}

static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
	glFlush();
}

static void handleKey(unsigned char key, int x, int y){
	
	if(key == 'r'){

		
		if(tempX >=0 && tempY >= 0){
			cout<<"starting render single"<<endl;
			renderSingle(cam, tempX, tempY);
		}
		else{
			cout<<"starting render"<<endl;
			render(cam);
		}
	}	
	if(key == 'c'){
		tempX = -1;
		tempY = -1;
		
		cout<<"setting temp x:"<<tempX<<" y:"<<tempY<<endl;
	}		
}

static void processMouse(int button, int state, int x, int y)
{
	y = height - y;  
	if(state == GLUT_UP){
		tempX = x;
		tempY = y;
		cout<<"x:"<<x<<" y:"<<y<<endl;
}
	//exit(0);               // Exit on mouse click.
}

void setupScene(){
	
	scene = Scene();
	
	//scene.objects.push_back(new Sphere(Vect(-15, 25, 80), 30));
	//scene.objects.push_back( new OBJ("tinyOBJ/pawn2.obj", Vect(-5,-15,60)));	
	scene.objects.push_back( new Plane(Vect(0, .99, .01), Vect (-300, -10, -50)) );	
	scene.objects.push_back( new Sphere(Vect(0, 0, 0), 20) );	
	scene.objects.push_back( new Sphere(Vect(-20, 0, 20), 20) );		
	scene.objects.push_back( new Sphere(Vect(20, 0, 20), 20) );	
	scene.objects.push_back( new Sphere(Vect(0, 0, 40), 20) );	
	scene.objects.push_back( new Sphere(Vect(-40, 0, 40), 20) );	
	scene.objects.push_back( new Sphere(Vect(40, 0, 40), 20) );	
	scene.objects.push_back( new Plane(Vect(0, 0, -1), Vect(0, 0, 200)) );	
	scene.objects.push_back( new Plane(Vect(0, 0, 1), Vect(0, 0, -150)) );	
	scene.objects.push_back( new Plane(Vect(-1, 0, 0), Vect(200, 0, 0)) );	
	scene.objects.push_back( new Plane(Vect(1, 0, 0), Vect(-200, 0, 0)) );	
	scene.objects.push_back( new Plane(Vect(0, -.99, .01), Vect(-200, 200, 0)) );	
	
	//scene.objects[0]->material->diffuse = white;
	scene.objects[7]->material->SetDiffuseMap("Textures/wood2_diff.bmp");
	scene.objects[8]->material->SetDiffuseMap("Textures/wood2_diff.bmp");
	scene.objects[9]->material->SetDiffuseMap("Textures/wood2_diff.bmp");
	scene.objects[10]->material->SetDiffuseMap("Textures/wood2_diff.bmp");
	scene.objects[11]->material->SetDiffuseMap("Textures/wood2_diff.bmp");
	
	scene.objects[0]->material->SetDiffuseMap("Textures/pool.bmp");
	
	scene.objects[1]->material->diffuse = COLOR(83.0/255.0,16.0/255.0,160.0/255.0);
	scene.objects[1]->material->reflection = 1;
	scene.objects[1]->material->transparency = 0;
	scene.objects[1]->material->ior = 2.2;
	
	scene.objects[2]->material->diffuse = COLOR(1.0/255.0,0.0/255.0,5.0/255.0);
	scene.objects[2]->material->reflection = 1;
	scene.objects[2]->material->transparency = 0;
	scene.objects[2]->material->ior = 2.2;
	
	scene.objects[3]->material->diffuse = COLOR(13.0/255.0,18.0/255.0,110.0/255.0);
	scene.objects[3]->material->reflection = 1;
	scene.objects[3]->material->transparency = 0;
	scene.objects[3]->material->ior = 2.2;
	
	scene.objects[4]->material->diffuse = COLOR(273.0/255.0,91.0/255.0,8.0/255.0);
	scene.objects[4]->material->reflection = 1;
	scene.objects[4]->material->transparency = 0;
	scene.objects[4]->material->ior = 2.2;
	
	scene.objects[4]->material->diffuse = COLOR(181.0/255.0,24.0/255.0,5.0/255.0);
	scene.objects[4]->material->reflection = 1;
	scene.objects[4]->material->transparency = 0;
	scene.objects[4]->material->ior = 2.2;
	
	scene.objects[5]->material->diffuse = COLOR(243.0/255.0,178.0/255.0,2.0/255.0);
	scene.objects[5]->material->reflection = 1;
	scene.objects[5]->material->transparency = 0;
	scene.objects[5]->material->ior = 2.2;
	
	
	//scene.objects[3]->material->diffuse = pink;
	
	//scene.lights.push_back( new areaLight(Vect(75,250, 0), Vect(1,.7,-.3), white, 200, 200) );
	//scene.lights.push_back( new areaLight(Vect(-100,50, 80), Vect(-1,0,0), COLOR(.5,.5,1.0), 100, 100) );
	scene.lights.push_back( new areaLight(Vect(100,100, -100), Vect(-.5,-.5,.5), COLOR(1.0,.85,.85), 50, 50) );
	scene.lights[0]->intensity = 20000;
	
	scene.lights.push_back( new areaLight(Vect(-100,0, -30), Vect(.5,0,.5), COLOR(.85,.85,1.0), 100, 100) );
	scene.lights[1]->intensity = 8000;
	
	scene.lights.push_back( new areaLight(Vect(0,80, 80), Vect(0,-.5,-.5), COLOR(.85,.85,1.0), 100, 100) );
	scene.lights[2]->intensity = 8000;
	
	scene.lights.push_back( new areaLight(Vect(0,100, 20), Vect(0,-.9,-.1), COLOR(.85,.85,1.0), 150, 150) );
	scene.lights[3]->intensity = 4000;
	
	//scene.lights.push_back( new spotLight(Vect(200, 80, 40), Vect(-1, -.3, 0), COLOR (.9, .85, .92), 80) );	
	
	return;
	
}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100); // Where the window will display on-screen.
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("P10: Distributed Ray Tracing");
	glClearColor(1,1,1,1); // Set background color.
	
	SetEasyBMPwarningsOff();
	cam = Camera( Vect(0,80,-60),Vect(0,-.4,.6),(float)height / (float)width, DOF );
	
	setupScene();
	//render(cam);
	
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKey);
	glutMouseFunc(processMouse);
	glutMainLoop();

	return 0;
}
	
