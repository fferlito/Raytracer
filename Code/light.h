#ifndef LIGHT_H_
#define LIGHT_H_

#include "triple.h"

// Declare LightPtr for use in Scene class
#include <memory>
class Light;
typedef std::shared_ptr<Light> LightPtr;

class Light
{
    public:
        Point const position;
        Color const color;

        Light(Point const &pos, Color const &c)
        :
            position(pos),
            color(c)
        {}
};

#endif
