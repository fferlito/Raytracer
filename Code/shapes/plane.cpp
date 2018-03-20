#include "plane.h"

#include <cmath>


using namespace std;

Hit Plane::intersect(Ray const &ray)
{
	// Unit normal
	Vector Pn(a, b, c);
	double Vd = Pn.dot(ray.D);
	if (Vd != 0) {
		// Determine if there is an intersection
		double Vo = -1 * (Pn.dot(ray.O) + d);
		double t = Vo/Vd;
		if (t < 0) {
			return Hit::NO_HIT();
		}
		// Reverse the normal if vd is bigger than 0
		if (Vd > 0)  {
			return Hit(t, -1*Pn);
		}
		else {
			return Hit(t, Pn);
		}
	}
	else {
		return Hit::NO_HIT();
	}
}

Point Plane::getTextureCoordinates(Point location) {
		return location;
}

Plane::Plane(double const a, double const b, double const c, double const d)
:
    a(a),
    b(b),
    c(c),
    d(d)
{}
