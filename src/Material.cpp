#include "Material.h"

Material::Material(){
	diffuse = blue;
	specular = 1;
	reflection = 0;
	transparency = 0;
	ior = 1;
	bump = 1;
}

Material::Material(COLOR diffuse, float specular)	: diffuse(diffuse), specular(specular)
{
	
}

Material::Material( const char* diffuse, const char* specular, const char* normal, const char* reflection, const char* transparency)
{
	diffuseMap.ReadFromFile(diffuse);
	specularMap.ReadFromFile(specular);
	normalMap.ReadFromFile(normal);
	reflectionMap.ReadFromFile(reflection);
	transpancyMap.ReadFromFile(transparency);
}

void Material::SetDiffuseMap(const char* d){
	diffuseMap.ReadFromFile(d);
}

COLOR Material::sampleTexture(BMP *texture, Vect2d uv){
		
		int i = uv.x * texture->TellWidth();
		int j = uv.y * texture->TellHeight();
		RGBApixel pixel = texture->GetPixel( i,j);
		
		//cout<<"sampling Texture for u:"<<uv.x<<" v: "<<uv.y<<endl;
		
		return COLOR(pixel.Red, pixel.Green, pixel.Blue);
		
}

COLOR Material::shade(Scene *scene, Intersection *intersection, Vect np, Vect npe, int depth){
	
	float bias = .01;
	float fresneleffect = 0;
	float kr = 0;
	
	COLOR pixelColor = COLOR(0.0, 0.0, 0.0);
	
	COLOR diffuseColor = COLOR(0.0, 0.0, 0.0);
	COLOR reflectionColor = COLOR(0.0, 0.0, 0.0);
	COLOR specularColor = COLOR(0.0, 0.0, 0.0);
	COLOR refractionColor = COLOR(0.0, 0.0, 0.0);
	COLOR shadowColor = COLOR(0.0, 0.0, 0.0);

	
	Vect pH = intersection->pH;
	Vect nH = intersection->nH.normalize();
	
	float b = 0;//object->GetBorderIntensity(nH, npe);
	
	//Calculate Diffuse and Specular Component
	
	//return diffuse;
	
	//return COLOR(nH.x/2 + .5, nH.y + .5, nH.z + .5);
		
	if(diffuseMap.TellWidth() > 1){
		diffuse = sampleTexture(&diffuseMap, intersection->object->GetUV(pH));
	}
	
	for(int i =0; i < scene->lights.size(); i++){
				
			Light *light = scene->lights[i];
			LightContribution lighting = light->GetLighting(scene, npe, pH, nH);
			
			diffuseColor += diffuse * light->color * lighting.diffuse;
			specularColor += light->color * lighting.specular;
	}

	if(reflection > 0 && transparency == 0 && depth < maxDepth){
		
		
		Utility::fresnel(npe, nH, ior, kr); 
		
		Vect reflectionDirection = Utility::reflect(npe, nH);
		Vect reflectionRayOrig = pH+(nH*bias); 
		
		
		Intersection reflection_intersection = RayTracer::trace(scene, reflectionRayOrig, reflectionDirection, depth+1);

	
		if(reflection_intersection.ti > 0){
			reflectionColor = reflection_intersection.object->material->shade(scene, &reflection_intersection, reflectionRayOrig, reflectionDirection, depth+1);
			reflectionColor = reflectionColor * reflection;
		}
	}
	
	else if(reflection > 0 && transparency > 0 && depth < maxDepth){
		
				Utility::fresnel(npe, nH, ior, kr); 
				bool outside = npe.dotProduct(nH) < 0; 
				
				if(kr < 1){
					
					Vect refractionDirection = Utility::refract(npe, nH, ior).normalize(); 
					Vect refractionRayOrig = outside ? pH-nH*bias : pH+nH*bias; 
					
					Intersection refraction_intersection = RayTracer::trace(scene, refractionRayOrig, refractionDirection, depth+1);
					if(refraction_intersection.ti > 0){
						refractionColor = refraction_intersection.object->material->shade(scene, &refraction_intersection, refractionRayOrig, refractionDirection, depth+1);
					}
				}
				
				Vect reflectionDirection = Utility::reflect(npe, nH);
				Vect reflectionRayOrig = pH+(nH*bias); 
				Intersection reflection_intersection = RayTracer::trace(scene, reflectionRayOrig, reflectionDirection, depth+1);
				
				if(reflection_intersection.ti > 0){
					reflectionColor = reflection_intersection.object->material->shade(scene, &reflection_intersection, reflectionRayOrig, reflectionDirection, depth+1);
				}
	}
	//cout<<kr<<endl;
	return(
			
			(refractionColor * (1 - kr)) + (reflectionColor * kr) + ((diffuseColor + specularColor) * (1-kr))
	);
}