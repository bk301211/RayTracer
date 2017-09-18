#include "Objects.h"
Object::Object(){
	material = new Material();
}

Plane::Plane(){
	normal = Vect(1, 0, 0).normalize();
	Pc = Vect(100, 0, 0);
	n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
	n1 = normal.normalize().crossProduct(n0).normalize();
	material = new Material();
}

Plane::Plane(Vect n, Vect cen){
	normal = n.normalize();
	Pc = cen;
	n0 = Vect(0, 1, 0).crossProduct(normal).normalize();
	n1 = normal.normalize().crossProduct(n0).normalize();
	material = new Material();
}

Vect Plane::GetSurfaceNormal(Vect hitPoint){
	return normal;
}

float Plane::GetBorderIntensity(Vect nH, Vect npe){
	return 0;
}


Intersection Plane::intersect(Vect rayOrigin, Vect rayDirection){
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

Vect2d Plane::GetUV(Vect pH){
	
		s0 = 50;
		s1 = 50;
		
		double U = abs((pH - Pc).dotProduct(n0) / s0);
		double V = abs((pH - Pc).dotProduct(n1) / s1);
		
		U -= trunc(U); //clips off the whole number, so 1.2 will become .2
		V -= trunc(V);
		
		return Vect2d(U,V);
}

	
Sphere::Sphere(){
	Pc = Vect(0, -5, 60);
	rad = 10;
	material = new Material();
}

Sphere::Sphere(Vect cen, float r){
	Pc = cen;
	rad = r;
	material = new Material();
}

Vect Sphere::GetSurfaceNormal(Vect hitPoint){
	
	return ((hitPoint - Pc)/rad).normalize();
}

float Sphere::GetBorderIntensity(Vect nH, Vect npe){
	float b = 1 - abs(npe.dotProduct(nH));
	b = b<0.7?0.0:b;
	b = b>1.0?1.0:b;
	return b;
}
	

Intersection Sphere::intersect(Vect rayOrigin, Vect rayDirection){
	
	float radiusSquared = rad*rad;
	float randY = 1;
	Vect L = Pc - rayOrigin; 
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
	intersection.nH = ((intersection.pH - Pc)/rad).normalize();
	
	return intersection;
	
}
Vect2d Sphere::GetUV(Vect pH){
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
		
		double u = theta/(M_PI*2);
		double v = phi/(M_PI*2);
		
		return Vect2d(u,v);
}



	
Triangle::Triangle(){
	
};

Triangle::Triangle(Vect idxp0, Vect idxp1, Vect idxp2, Vect2d uv1, Vect2d uv2, Vect2d uv3, Vect nm1, Vect nm2, Vect nm3){

p0 = idxp0;
p1 = idxp1;
p2 = idxp2;
n0 = nm1;
n1 = nm2;
n2 = nm3;
UV1 = uv1;
}

Triangle::Triangle(Vect idxp0, Vect idxp1, Vect idxp2, Vect2d uv1, Vect2d uv2, Vect2d uv3){
p0 = idxp0;
p1 = idxp1;
p2 = idxp2;
}
/*
Intersection Triangle::intersect(Vect rayOrigin, Vect rayDirection){//Vect *verts;
	Vect pH;
	float ti;
	float u, v;
	int i = 0;
	//tinyobj::index_t idx = 0;
	//tinyobj::attrib_t attrib;
	
	
	//attrib[]
	//cout<<"Here1"<<endl;
	//cout<<"attrib"<<attrib.vertices[i]<<endl;
	//p0 = Vect(attrib.vertices[i],attrib.vertices[i+1],attrib.vertices[i+2]);
	//cout<<"Here2"<<endl;
	//p1 = Vect(attrib.vertices[i+3], attrib.vertices[i+4], attrib.vertices[i+5]);
	//p2 = Vect(attrib.vertices[i+6], attrib.vertices[i+7], attrib.vertices[i+8]);
	//
	//compute plane of triangle normal
	//Vect A  = (p1-p0).crossProduct(p2-p0);
	//Vect n = A.normalize();
	
	Vect n = (n0+n1+n2)/3;
	n = n*(-1);
	
	float area = n.magnitude()/2;
	
	Vect rayVect = p0 - rayOrigin;
	float a = n.dotProduct(rayDirection); //NdotDir
	float D = n.dotProduct(p0);
	
	if (a >= 0) return Intersection(0);
	
	else{
	
		ti = fabs((n.dotProduct(rayOrigin)+D)/ a);
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
		
		///////v = (C.magnitude()/2) / area;
		
		if(rayDirection.dotProduct(C)<0) return Intersection(0);
		//cout<<ti<<endl;
		
		
		Intersection intersection;
		intersection.ti = ti;
		intersection.nH = n;
		intersection.pH = pH;
		//cout<<"returning intersection: "<<n<<" ph: "<<pH<<endl;
		return intersection;
		
	}
}*/
/*
Intersection Triangle::intersect(Vect rayOrigin, Vect rayDirection){//Vect *verts;
	float u, v;
	
	Vect p0p1 = p1 - p0;
	Vect p0p2 = p2 - p0;
	
	//float area2 = planeNormal.magnitudeSquared();
	
	//cout<<"p0: "<<p0<<" p1: "<<p1<<" p2: "<<p2<<endl;
	
	
	Vect planeNormal = p0p1.crossProduct(p0p2).normalize();
	


	float NDotRayDirection = planeNormal.dotProduct(rayDirection);
	
	
	if(fabs(NDotRayDirection) < .00001)
		return Intersection(0);

	float D = planeNormal.dotProduct(p0);
	cout<<"D:"<<D<<endl;
	cout<<"planeNormal: "<<planeNormal<<endl;
	cout<<"NDotRayDirection: "<<NDotRayDirection<<endl;
	float ti = (planeNormal.dotProduct(rayOrigin) + D) / -(NDotRayDirection);
	cout<<"ti:"<<ti<<endl;		
	cout<<"p0: "<<p0<<" p1: "<<p1<<" p2: "<<p2<<endl<<endl;	
	

	//triangle is behind ray
	
	if(ti<0){
		return Intersection(0);
	}
	//}//return ti;
	
	
	//cout<<"rayOrigin: "<<rayOrigin<<" rayDirection: "<<rayDirection<<endl;
	Vect planeHit = rayOrigin + (rayDirection * ti);
	//cout<<planeHit<<endl;
	
	Vect C;
	
	Vect edge0 = p1-p0;
	//Vect edge0 = p0-p1;
	Vect vp0 = planeHit - p0;
	C = edge0.crossProduct(vp0);
	//C = vp0.crossProduct(edge0);
	if(rayDirection.dotProduct(C)<0) return Intersection(0);
	Vect edge1 = p2-p1;
	//Vect edge1 = p1-p2;
	Vect vp1 = planeHit - p1;
	C = edge1.crossProduct(vp1);
	//C = vp1.crossProduct(edge1);
	//u = (C.magnitude()/2) / area;
	if(rayDirection.dotProduct(C)<0) return Intersection(0);
	
	Vect edge2 = p0-p2;
	//Vect edge2 = p2-p0;
	Vect vp2 = planeHit - p2;
	C = edge2.crossProduct(vp2);
	if(rayDirection.dotProduct(C)<0) return Intersection(0);
	//cout<<ti<<endl;
	
	
	Intersection intersection;
	intersection.ti = ti;
	intersection.nH = planeNormal;
	intersection.pH = planeHit;
	
	
	return intersection;
		
}*/

Intersection Triangle::intersect(Vect rayOrigin, Vect rayDirection){//Vect *verts;
	
	
	Vect e1 = p1 - p0;
    Vect e2 = p2 - p0;
	
	Vect planeNormal = e1.crossProduct(e2).normalize();
    // Calculate planes normal vector
    Vect pvec = rayDirection.crossProduct(e2);
    float det = e1.dotProduct(pvec);

    // Ray is parallel to plane
    if (det < 1e-8 && det > -1e-8) {
        return Intersection(0);
    }

    float inv_det = 1 / det;
    Vect tvec = rayOrigin - p0;
    float u = tvec.dotProduct(pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }

    Vect qvec = tvec.crossProduct(e1);
    float v = rayDirection.dotProduct(qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return 0;
    }
    float ti = e2.dotProduct(qvec) * inv_det;
	
	Intersection intersection;
	intersection.ti = ti;
	intersection.nH = planeNormal;
	intersection.pH = rayOrigin + (rayDirection*ti);
	
	return intersection;
		
}

Vect Triangle::GetSurfaceNormal(Vect hitPoint){
	
	Vect A  = (p1-p0).crossProduct(p2-p0);
	Vect n = A.normalize();
	
	return n;
}


Intersection OBJ::intersect(Vect rayOrigin, Vect rayDirection){
	Intersection minimumIntersection = Intersection();
	float tMin = INT_MAX;
	float ti = 0;
	
	for (int i = 0; i < tris.size(); i++){
		
		Intersection intersection = tris[i].intersect(rayOrigin, rayDirection);
		
		ti = intersection.ti;
		
		if( ti > 0 && ti < tMin){
			tMin = ti;
			minimumIntersection = intersection;
		}
	}
	return minimumIntersection;
}
	
Vect OBJ::GetSurfaceNormal(Vect hitPoint){
	
}

Vect2d OBJ::GetUV(Vect pH){
	return Vect2d(0,0);
}

OBJ::OBJ(string filename, Vect position){
	
	
	int TempNumOne = filename.size();
	char path[sizeof(filename)];
	
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

		if (hasNormals)
		{
			//tris.push_back(Triangle(v1, v2, v3, col, uv1, uv2, uv3));
			//cout<<"pushing triangle"<<endl<<v1<<endl<<v2<<endl<<v3<<endl<<endl;
			tris.push_back(Triangle(v1+position, v2+position, v3+position, uv1, uv2, uv3, nm1, nm2, nm3));
			//tris.push_back(Triangle(v1, nm1, uv1, v2, nm2, uv2, v3, nm3, uv3));
		}
		else
		{
			//cout<<"pushing triangle"<<endl<<v1<<endl<<v2<<endl<<v3<<endl<<endl;
			tris.push_back(Triangle(v1+position, v2+position, v3+position, uv1, uv2, uv3));
			
		}
	}
	cout << "Finished reading " << filename << "\n";
	fclose(file);
};