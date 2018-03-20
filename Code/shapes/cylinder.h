#ifndef CYLINDER_H
#define CYLINDER_H

#include "../object.h"

class Cylinder: public Object
{
public:
    Cylinder(Vector origin, Vector direction, double height, double radius);

    virtual Hit intersect(Ray const &ray);
    virtual Point getTextureCoordinates(Point location);

    Vector O; //origin
    Vector D; //axis
    double r; //radius length
    double h; //height

    Vector clip; //landmark vector for u coordinates
    double angle; //texture rotation around axis
};

#endif
