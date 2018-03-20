#ifndef RAY_H_
#define RAY_H_

#include "triple.h"

class Ray
{
    public:
        Point O;        // origin
        Vector D;       // direction of the ray

        Ray(Point const &from, Vector const &dir)
        :
            O(from),
            D(dir)
        {}

        Point at(double t) const
        {
            return O + t * D;
        }
};

#endif
