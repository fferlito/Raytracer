#ifndef PLANE_H_
#define PLANE_H_

#include "../object.h"

class Plane: public Object
{
    public:
        Plane(double const a, double const b, double const c, double const d);

        virtual Hit intersect(Ray const &ray);
		virtual Point getTextureCoordinates(Point location);
        double const a,b,c,d;
};

#endif
