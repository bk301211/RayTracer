#ifndef _INTERSECTION_H
#define _INTERSECTION_H

#include "Vect.h"
#include "Objects.h"

class Object;

struct Intersection{
	public:
	float ti;
	Vect nH;
	Vect pH;
	Object *object;
	
	Intersection(const float ti, const Vect nH, const Vect pH, Object *object)
	: ti(ti), nH(nH), pH(pH), object(object)
	{}
	
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
	: ti(-1), nH(Vect()), pH(Vect())
	{}
};

#endif