#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"

class Sphere: public Object
{
    public:
        Sphere(Point const &pos, double radius);
        Sphere(Point const &pos, double radius, Vector &rotation, double angle);
        virtual Hit intersect(Ray const &ray);
		virtual Point getTextureCoordinates(Point location);
        
        Point const position;
        double const r;
        Vector rotation;
        double angle;
};

#endif
