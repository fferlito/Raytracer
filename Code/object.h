#ifndef OBJECT_H_
#define OBJECT_H_

#include "material.h"

// not really needed here, but deriving classes may need them
#include "hit.h"
#include "ray.h"
#include "triple.h"

#include <memory>
#include <string>

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Object
{
    public:
        Material material;
		
		bool hasTexture;
		
		std::string texturePath;
        virtual ~Object() = default;

        virtual Hit intersect(Ray const &ray) = 0;  // must be implemented
                                                  // in derived class
                                                  
		virtual Point getTextureCoordinates(Point location) = 0;
};

#endif
