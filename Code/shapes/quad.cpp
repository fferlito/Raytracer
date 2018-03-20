#include "quad.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Quad::intersect(Ray const &ray)
{  
	// Treat a quad as a polygon to determine intersection
	
	Vector n = (v1-v0).cross(v2-v0);
	n = n.normalized();
	
	double t = (v0 - ray.O).dot(n) / ray.D.dot(n);
	
	// Calculate the intersection point
	Vector p = ray.O + ray.D * t;
	
	if (t >= 0) {
		// Check if the intersection point lies within the polygon boundaries
		if (!((p - v0).dot(n.cross(v1-v0)) >= 0)) {
			return Hit::NO_HIT();	
		}
		
		if (!((p - v1).dot(n.cross(v2-v1)) >= 0)) {
			return Hit::NO_HIT();
		}
		
		if (!((p - v2).dot(n.cross(v3-v2)) >= 0)) {
			return Hit::NO_HIT();
		}
		
		if (!((p - v3).dot(n.cross(v0-v3)) >= 0)) {
			return Hit::NO_HIT();
		}
		return Hit(t,n);
	}
	else {
		return Hit::NO_HIT();
	}
}

Point Quad::getTextureCoordinates(Point location) {
		return location;
}

Quad::Quad(Point const &v0, Point const &v1, Point const &v2, Point const &v3)
:
    v0(v0),
    v1(v1),
    v2(v2),
    v3(v3)
{}
