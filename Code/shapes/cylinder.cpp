#include "cylinder.h"

#include <cmath>

using namespace std;

Hit Cylinder::intersect(Ray const &ray)
{
    //the axis of the cylinder is also a parametrized line, with equation
    //O + height*D, with 0<=height<=h. The projection of a point P on the
    //given ray, onto this axis, is also in function of t. In particular we
    //have height = k + j*t (with k and j below defined)

    double k = -(D.dot(O-ray.O))/D.length_2();
    double j = (D.dot(ray.D))/D.length_2();

    //top and bottom circles intersection

    //find t where projection is the center of the top circle
    double top_t = (h-k)/j;
    //find t where projection is the center of the bottom circle
    double bottom_t = (-k)/j;

    bool at_extreme = true; //if there is an intersection with one of the bases
    Hit failure = Hit::NO_HIT();   //if no intersection with side, return intersection with bases (if there)

    //discard later and negative intersection
    double extreme_t = min(top_t,bottom_t);
    if(extreme_t<0){
        extreme_t = max(top_t,bottom_t);
        if(extreme_t<0){
            at_extreme = false;
        }
    }

    if(at_extreme) {
        //normal is either the direction (top base) or its inverse (bottom base)
        Vector extreme_N = (top_t < bottom_t) ? (D + 0.0) : (-D);
        //center of selected base (O or O plus the direction, as long as the height)
        Vector center = (top_t < bottom_t) ? (O + D * h) : (O);
        //get if base intersection
        at_extreme = (ray.at(extreme_t) - center).length() <= r;

        //what to return in case there is no side intersection (there might be one with the base)
        failure = (!at_extreme) ? (Hit::NO_HIT()) : (Hit(extreme_t, extreme_N));
    }


    //components of second degree equation for distance between point on ray P and cylinder axis
    Vector dir = ray.D - D*j;
    Vector ori = ray.O - O - D*k;

    //a,b, and c components
    double a = dir.length_2();
    double b = 2*dir.dot(ori);
    double c = ori.length_2() - r*r;

    //nominator addends of the abc formula
    double term_first  = -b;
    double term_second = b*b -4*a*c;

    //check if intersection
    if(term_second<0)
        return failure;

    //get two intersection values
    double t1 = (term_first+sqrt(term_second))/(2*a);
    double t2 = (term_first-sqrt(term_second))/(2*a);

    //discard lower and negative time
    double t = min(t1,t2);
    if(t<0){
        t = max(t1,t2);
        if(t<0){
            return failure;
        }
    }

    //get intersection point and projection height
    Vector P = ray.at(t);
    double height = t*j + k;

    //check if projection in height limit of cylinder
    if(height<0 || height>h)
        return failure;

    //normal is vector from projection (on axis) to P
    Vector N = (P - (O+height*D)).normalized();
    return (extreme_t < t && at_extreme)?(failure):(Hit(t,N));
}

Point Cylinder::getTextureCoordinates(Point location) {
  
    return Point(0,0.0);
}

Cylinder::Cylinder(Vector origin, Vector direction, double height, double radius)
        :
        O(origin), //center of base (circle)
        D(direction.normalized()), //normalized direction (axis of cylinder)
        r(radius), //radius of cylinder
        h(height) //height of cylinder

        //clip(),
        //angle(ang)    // used for texture
{}
