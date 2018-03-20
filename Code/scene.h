#ifndef SCENE_H_
#define SCENE_H_

#include "light.h"
#include "object.h"
#include "triple.h"

#include <vector>

// Forward declerations
class Ray;
class Image;

class Scene
{
    std::vector<ObjectPtr> objects;
    std::vector<LightPtr> lights;   // no ptr needed, but kept for consistency
    Point eye;
	bool hasShadow;
    bool hasToonShadingOn;
    unsigned superSamplingFactor;
	unsigned maxReflectionDepth;
	
    public:
		
        // trace a ray into the scene and return the color
        Color trace(Ray const &ray);
        Color reflectRayRecursive(Ray const &ray, unsigned reflectCount);
        bool reflectRayIntersection(Ray const &ray);
        
        // render the scene to the given image
        void render(Image &img);

        void addObject(ObjectPtr obj);
        void addLight(Light const &light);
        void setEye(Triple const &position);
        void setHasShadow(bool const &shadow);
        void setToonShading(bool const &toon);
        void setReflectionDepth(unsigned const &maxDepth);
        void setSuperSamplingFactor(unsigned const &factor);
        unsigned getNumObject();
        unsigned getNumLights();
};

#endif
