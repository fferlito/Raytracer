#ifndef QUAD_H_
#define QUAD_H_

#include "../object.h"

class Quad: public Object
{
    public:
        Quad(Point const &v0, Point const &v1, Point const &v2, Point const &v3);

        virtual Hit intersect(Ray const &ray);
		virtual Point getTextureCoordinates(Point location);
        Point const v0,v1,v2,v3;
};

#endif
