#include "sphere.h"
#include "solvers.h"

#include <cmath>

#define PI 3.14159265

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    // Sphere formula: ||x - position||^2 = r^2
    // Line formula:   x = ray.O + t * ray.D

    Vector L = ray.O - position;
    double a = ray.D.dot(ray.D);
    double b = 2 * ray.D.dot(L);
    double c = L.dot(L) - r * r;

    double t0;
    double t1;
    if (not Solvers::quadratic(a, b, c, t0, t1))
        return Hit::NO_HIT();

    // t0 is closest hit
    if (t0 < 0)  // check if it is not behind the camera
    {
        t0 = t1;    // try t1
        if (t0 < 0) // both behind the camera
            return Hit::NO_HIT();
    }

    // calculate normal
    Point hit = ray.at(t0);
    Vector N = (hit - position).normalized();

    // determine orientation of the normal
    if (N.dot(ray.D) > 0)
        N = -N;

    return Hit(t0, N);
}

Point Sphere::getTextureCoordinates(Point location) {
	Point n = location - position;
	
	if (angle != 0) {
		// Use the rodrigues rotation formula to calculate the rotated vector
		n = n * cos(-(angle*PI)/180.0) + rotation.cross(n) * sin(-(angle*PI)/180.0) + rotation * rotation.dot(n) * (1 - cos(-(angle*PI)/180.0));
	}
	
	// Calculate u, v coordinates
	Point uvCoor;
	double theta = acos(n.z/r);
	double phi = atan2(n.y, n.x);
	if (phi < 0) {
		phi += 2*PI;
	}
	uvCoor.x = phi/ (2*PI) ;
	uvCoor.y = 1 - (PI - theta) / PI;
	
	return uvCoor;
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}

Sphere::Sphere(Point const &pos, double radius, Vector &rotation, double angle)
:
    position(pos),
    r(radius),
    rotation(rotation),
    angle(angle)
{}

