#include "Lights.h"

pointLight::pointLight(){
	pos = Vect(0, 5, 0);
	color = white;
}

pointLight::pointLight(Vect p, COLOR c){
	pos = p;
	color = c;
}

LightContribution pointLight::GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH){
	
	Vect nLH, V, R;
	float d, b, sMin, sMax, s, phi;
	float exp = 10;

	
	nLH = (pos- pH).normalize();
	d = ((nH.dotProduct(nLH)+1)/2);
	//d = ((nH.dotProduct(nLH)));
	
	R = nLH.negative() + (nH*(nLH.dotProduct(nH))*2);
	V = npe.negative();
	phi = V.dotProduct(R);
	sMax = max((float)0, phi);
	sMin = min((float)0, phi);
	
	/////////
	// use this s for hard specular
	/////////
	//s = (phi - sMin)/(sMax - sMin);
	
	////////
	//use this s for sof specular
	/////////
	s = pow(sMax, exp) * abs(nH.dotProduct(nLH));
	
	s = s<0?0:s;
	s = s>1?1:s;
	
	return LightContribution(d, s);
}



dirLight::dirLight(){
	dir = Vect(.9, .8, 0);
	color = white;
}

dirLight::dirLight(Vect d, COLOR c){
	dir = d;
	color = c;
}

LightContribution dirLight::GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH){
	Vect nLH, V, R;
	float d, sMin, sMax, s, phi;
	float exp = 10;
	
	nLH = dir.normalize();
	d = (nH.dotProduct(nLH)+1)/2;
	
	R = nLH.negative() + (nH*(nLH.dotProduct(nH))*2);
	V = npe.negative();
	phi = V.dotProduct(R);
	sMax = max((float)0, phi);
	sMin = min((float)0, phi);
	
	/////////
	// use this s for hard specular
	/////////
	//s = (phi - sMin)/(sMax - sMin);
	
	////////
	//use this s for sof specular
	/////////
	s = pow(sMax, exp) * abs(nH.dotProduct(nLH));
	
	s = s<.6?0:s;
	s = s>1?1:s;
	
	return LightContribution(d, s, 0);
}


spotLight::spotLight(){
	pos = Vect(0 , 5, 0);
	dir = Vect(.9, .8, 0);
	color = white;
	//float theta = 3.14/4;
	theta = 30.0;
}

spotLight::spotLight(Vect p, Vect d, COLOR c, float ang){
	pos = p;
	dir = d;
	color = c;
	theta = ang;
}

LightContribution spotLight::GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH){
	Vect nLH, V, R, pHL;
	float d, sMin, sMax, s, phi;
	float exp = 10;
	float a = 1;
	
	float cosAngle = cos(theta*0.017453);
	float x = (pH - pos).normalize().dotProduct(dir);
	
	bool occluded = RayTracer::fastTrace(scene, pH + (nH * bias), (pos-pH).normalize(), (pos - pH).magnitudeSquared() );	
	
	if(x > cosAngle){
		nLH = (pos-pH).normalize();
		pHL = (pos-pH);
		
		d = (nH.dotProduct(nLH)+1)/2;
		
		R = nLH.negative() + (nH*(nLH.dotProduct(nH))*2);
		V = npe.negative();
		phi = V.dotProduct(R);
		sMax = max((float)0, phi);
		sMin = min((float)0, phi);
		
		s = pow(sMax, exp) * abs(nH.dotProduct(nLH));
		
		s = s<0?0:s;
		s = s>1?1:s;
	}
	else{
		
		d = 0;
		s = 0;
	}
	
	return LightContribution(d, s, occluded? 1 : 0);
}

areaLight::areaLight(){
	pos = Vect(0 , 5, 0);
	dir = Vect(.9, .8, 0);
	color = white;
	//float theta = 3.14/4;
	theta = 30.0;
}

areaLight::areaLight(Vect p, Vect d, COLOR c, float w, float h){
	pos = p;
	dir = d;
	color = c;
	width = w;
	height = h;
	samples = 4;
	intensity = 20000;
	
	Vect vup = Vect(0, 1, 0);
	
	
	
	n0 = vup.crossProduct(dir).normalize();
	Vect n2 = dir.normalize();
	n1 = n2.crossProduct(n0).normalize();
	p0 = pos - (n0 * (width / 2)) - (n1 * (height / 2));
	
	//cout<<dir<<endl;
	//cout<<n0<<endl;
	//cout<<n1<<endl;
	//cout<<p0<<endl;
}

LightContribution areaLight::GetLighting(Scene *scene, Vect npe, Vect pH, Vect nH){
	
	LightContribution lighting = LightContribution(0,0);
	
	
	for(int i = 0; i < samples; i++){
		for(int j = 0; j < samples; j++){
			
			float randomX = (float)rand()/(float)RAND_MAX;
			float randomY = (float)rand()/(float)RAND_MAX;
			
			Vect lightPoint = p0 + (n0 * (((float)i + randomX)/samples) * width)
										+ 
									(n1 * (((float)j + randomY)/samples) * height);
									
			
									
			
			//cout<<(((float)i + randomX)/samples) * width<<endl;
			//cout<<(((float)j + randomY)/samples) * height<<endl;			
			
			
			Vect hitPointToLight = (lightPoint - pH);
			
			bool occluded = RayTracer::fastTrace(scene, pH + (nH * bias), hitPointToLight.normalize(), hitPointToLight.magnitudeSquared());

			//cout<<"is occluded:"<<occluded<<endl;			
			/*
			if(!occluded){
				
				lighting.diffuse += 1.0 * 1/(lightPoint - pH).magnitudeSquared() * intensity;
				
				Vect half = Utility::halfAngle(npe * -1, hitPointToLight);
				
				if(fabs(half.dotProduct(nH)) < .01)
					lighting.specular+=1;
					//cout<<half.dotProduct(nH)<<endl;
				
				lighting.specular += 0 * 1/(lightPoint - pH).magnitudeSquared() * intensity;
				
				
				
				lighting.occlusion += 0.0;
				
			}
			else{
				lighting.occlusion += 1.0;
			}*/
			
			
			
			if(!occluded){
				Vect nLH, V, R;
				float d, sMin, sMax, s, phi;
				float exp = 10;
				
				nLH = dir.normalize() *-1;
				//cout<<nLH<<endl;
				d = (nH.dotProduct(nLH)+1)/2;
				
				R = nLH.negative() + (nH*(nLH.dotProduct(nH))*2);
				V = npe.negative();
				phi = V.dotProduct(R);
				sMax = max((float)0, phi);
				sMin = min((float)0, phi);
				
				/////////
				// use this s for hard specular
				/////////
				//s = (phi - sMin)/(sMax - sMin);
				
				////////
				//use this s for sof specular
				/////////
				s = pow(sMax, exp) * abs(nH.dotProduct(nLH));
				
				s = s<0?0:s;
				s = s>1?1:s;
				
				lighting.diffuse +=d * 1/(lightPoint - pH).magnitudeSquared() * intensity;
				lighting.specular +=s * 1/(lightPoint - pH).magnitudeSquared() * intensity;
				
				//lighting.occlusion += RayTracer::fastTrace(scene, pH + (nH * bias), hitPointToLight, (lightPoint - pH).magnitudeSquared())? 1.0 : 0.0; 
			}
			else{
				//occluded = RayTracer::fastTrace(scene, pH + (nH * bias), hitPointToLight, (lightPoint - pH).magnitudeSquared() );
				lighting.occlusion += 1.0;
			}
			
		}	
	}
	
	float totalSamples = samples * samples;
	
	lighting.diffuse = lighting.diffuse / totalSamples;
	lighting.specular = lighting.specular / totalSamples;
	lighting.occlusion = lighting.occlusion / totalSamples;
	
	//cout<<"lighting diffuse:"<<lighting.diffuse<<endl;
	//cout<<"lighting specular:"<<lighting.specular<<endl;
	//cout<<"lighting occlusion:"<<lighting.occlusion<<endl;
	
	//lighting.occlusion = 0;
	return lighting;
}