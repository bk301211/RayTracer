#ifndef _UTILITY_H
#define _UTILITY_H

#include "math.h"
#include "Vect.h"
#include "Vect2D.h"
#include <iostream>
#include <stdint.h>

class Utility{
	public:
	static float mix(const float &a, const float &b, const float &mix)
	{
		return b * mix + a * (1 - mix);
	}

	static Vect reflect(Vect rayDirection, Vect hitNormal)
	{ 
		Vect reflectDir = rayDirection - hitNormal*(rayDirection.dotProduct(hitNormal))*2;
		return reflectDir.normalize();
	} 

	static Vect refract(Vect I, Vect N, const float &ior) 
	{ 
		float cosi = I.dotProduct(N);
		cosi = cosi < -1 ? -1 : cosi > 1? 1 : cosi;
		
		float etai = 1, etat = ior; 
		Vect n = N; 
		if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= N * -1; } 
		float eta = etai / etat; 
		float k = 1 - eta * eta * (1 - cosi * cosi); 
		return k < 0 ? Vect() : I * eta  + n * (eta * cosi - sqrtf(k)); 
	} 
	
	static Vect halfAngle(Vect cameraDirection, Vect lightDirection){
		
		return (lightDirection.normalize() + cameraDirection.normalize()).normalize();
		
			/*
	light_vect = light_position - face_center_position
	cam_vect = cam_position - face_center_position
	halfangle_vect = (light_vect.normal() + cam_vect.normal()).normal()
	*/
	}
	
	static void fresnel(Vect I, Vect N, const float &ior, float &kr) 
	{ 				
		float cosi = I.dotProduct(N);
		cosi = cosi < -1 ? -1 : cosi > 1? 1 : cosi;
		
		float etai = 1, etat = ior; 
		if (cosi > 0) { std::swap(etai, etat); } 
		// Compute sini using Snell's law
		float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi)); 
		// Total internal reflection
		if (sint >= 1) { 
			kr = 1; 
		} 
		else { 
			float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
			cosi = fabsf(cosi); 
			float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
			float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
			kr = (Rs * Rs + Rp * Rp) / 2; 
		} 
		// As a consequence of the conservation of energy, transmittance is given by:
		// kt = 1 - kr;
	}
};
#endif