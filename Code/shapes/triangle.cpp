#include "triangle.h"

#include <cfloat>   // DBL_EPSILON
#include <cmath>

Hit Triangle::intersect(Ray const &ray)
{
    // Möller-Trumbore
    Vector edge1(v1 - v0);
    Vector edge2(v2 - v0);
    Vector h = ray.D.cross(edge2);
    double a = edge1.dot(h);
    if (a > -DBL_EPSILON && a < DBL_EPSILON)
        return Hit::NO_HIT();

    double f = 1 / a;
    Vector s = ray.O - v0;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return Hit::NO_HIT();

    Vector q = s.cross(edge1);
    double v = f * ray.D.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return Hit::NO_HIT();

    double t = f * edge2.dot(q);

    if (t <= DBL_EPSILON)    // line intersection (not ray)
        return Hit::NO_HIT();

    // determine orientation of the normal
    Vector normal = N;
    if (N.dot(ray.D) > 0)
        normal = -normal;

    return Hit(t, normal);
}

Point Triangle::getTextureCoordinates(Point location) {
		return location;
}

Triangle::Triangle(Point const &v0,
         Point const &v1,
         Point const &v2)
:
    v0(v0),
    v1(v1),
    v2(v2),
    N()
{
    // Calculate surface normal
    Vector U(v1 - v0);
    Vector V(v2 - v0);
    N = U.cross(V);
    N.normalize();
}
