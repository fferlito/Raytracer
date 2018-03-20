#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>
#include <iostream>

#define toonA 0.1
#define toonB 0.25
#define toonC 0.3
#define toonD 1

using namespace std;

Color Scene::trace(Ray const &ray)
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));

        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }
    // No hit? ReturN background color.
	if (!obj) return Color(0.0, 0.0, 0.0);
	
    Material material = obj->material;          //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector + Vector    vector sum
    *        Vector - Vector    vector difference
    *        Point - Point      yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double * Color     scales each color component (r,g,b)
    *        Color * Color      dito
    *        pow(a,b)           a to the power of b
    ****************************************************/
    
    // Set the correct color of the point based on a texture or the color of the material.
    Color materialColor;
    if (material.useTexture) {
		Point textureCoordinates = obj->getTextureCoordinates(hit);
		materialColor = material.texture.colorAt(textureCoordinates.x, textureCoordinates.y);
	}
	else {
		materialColor  = material.color;
	}
   
    
    
        
    // Toon shading computation: make steep change in diffuse color
    N = N.normalized();
    float VdotN = V.dot(N);
    if(VdotN < 0.3 && hasToonShadingOn) return Vector(0,0,0);
    
    
    // Compute Full Phong Lightinig Model
    // add bias to hit point of ray (otherwise it bounces on surface)
    hit += 0.0001 * N;
    
    Vector sumLights(0,0,0);
    Vector reflect(0,0,0);
    
    // loop over all lights and compute diffuse and specular compoments
    for (unsigned i = 0; i < getNumLights(); i++) {
		
		Vector L = (lights[i]->position - hit).normalized();      // direction of light
		if (hasShadow) {
			if (reflectRayIntersection(Ray(hit, L))) {
				// Skip this light for color calculation as the ray intersects another object
				continue;
			}
		}
	    Vector R = (2 * N.dot(L) * N - L).normalized();           // direction of (ideal) reflection towards light
	    
        float LdotN = N.dot(L);
        
        // Toon shading computation: make steep change in diffuse color
        if(hasToonShadingOn == true){
          if (LdotN < toonA) {
            LdotN = 0.0;
          }
          else if (LdotN < toonB) LdotN = toonB;
          else if (LdotN < toonC) LdotN = toonC;
          else LdotN = toonD;
        } 
        
		Vector diffuse =  fmax(0, LdotN) * materialColor * lights[i]->color * material.kd;
		

        // Toon shading computation: make specular component less smooth
        float RdotV = R.dot(V.normalized());
        if(hasToonShadingOn){
        if (RdotV < 0.95) 
          RdotV = 0.0;
        else 
          RdotV = 1.0;
        } 
        
		Vector specular = pow(fmax(0,RdotV), material.n) * lights[i]->color * material.ks;
        sumLights +=  specular + diffuse;	
      
    }
	// Ambient component (independent of light)
    Vector ambient = material.ka * material.color;
    
    if (material.ks != 0) {
		Vector R_reflect = (2 * N.dot(V) * N - V).normalized();    
		reflect = reflectRayRecursive(Ray(hit, R_reflect), maxReflectionDepth) * material.ks;
	}
    // Final color is the diffuse and specular (sumlights) + the ambient part and reflect
    Color color = sumLights + ambient + reflect; 
    
    return color;           
}

// Method to see if when the ray continues it would intersect an object for the shadow calculation
bool Scene::reflectRayIntersection(Ray const &ray) {
		    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));

        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }
    if (!obj) {
		return false;
	}
    return true;
}

// Method for calculating the reflect color recursively
Color Scene::reflectRayRecursive(Ray const&ray, unsigned reflectCount) {

    // Base case 1: maximal depth of recursion reached
    if(reflectCount == 0)   return Color(0.0,0.0,0.0);
    	
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));

        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }
    
    // Base case 2: reflacted ray doesn't hit any object
    // Return background color
    if (!obj) return Color(0.0, 0.0, 0.0);
	
    Material material = obj->material;             //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    N = N.normalized();
    Vector V = -ray.D;    
                             //the view vector
    Color materialColor;
    if (material.useTexture) {
		Point textureCoordinates = obj->getTextureCoordinates(hit);
		materialColor = material.texture.colorAt(textureCoordinates.x, textureCoordinates.y);
	}
	else {
		materialColor  = material.color;
	} 
    
    // Compute Full Phong Lightinig Model
    
    // Ambient component (independent of light)
    Vector ambient = material.ka * material.color;
    
    // add bias to hit point of ray (otherwise it bounces on surface)
    hit += 0.0001 * N;
    
    Vector sumLights(0,0,0);
    Vector reflect(0,0,0);
    
    // loop over all lights and compute diffuse and specular compoments
    for (unsigned i = 0; i < getNumLights(); i++) {
		
		Vector L = (lights[i]->position - hit).normalized();      // direction of light
		if (hasShadow) {
			if (reflectRayIntersection(Ray(hit, L))) {
				// Skip this light for color calculation as the ray intersects another object
				continue;
			}
		}
	    Vector R = (2 * N.dot(L) * N - L).normalized();           // direction of (ideal) reflection towards light
	    
		Vector diffuse =  fmax(0, N.dot(L)) * materialColor * lights[i]->color * material.kd;
		
		Vector specular = pow(fmax(0,R.dot(V.normalized())), material.n) * lights[i]->color * material.ks;

        sumLights +=  specular + diffuse;
	}
    if (material.ks != 0) {
		Vector R_reflect = (2 * N.dot(V) * N - V).normalized();    
		reflect = reflectRayRecursive(Ray(hit, R_reflect), maxReflectionDepth) * material.ks;
	}
    // Final color is the diffuse and specular (sumlights) + the ambient part 	
    Color color = sumLights + ambient + reflect; 
    
    return color; 
}

void Scene::render(Image &img)
{
    
      unsigned w = img.width();
      unsigned h = img.height();
      
      
      // create image
      for (float y = 0; y < h; ++y)
      {
          for (float x = 0; x < w; ++x)
          {
            
            Color sampledCol;
            
            for(float z = 0 ; z < superSamplingFactor; z ++){
              for(float w = 0 ; w < superSamplingFactor; w ++){
                
                float indexX= x + z / superSamplingFactor;
                float indexY = y + z / superSamplingFactor;
                Point pixel(indexX + 0.5, h - 1 - indexY + 0.5, 0);
                Ray ray(eye, (pixel - eye).normalized());
                Color tempColor = trace(ray);
                sampledCol += tempColor;
              }
            }
            // Average the sampled color over the samples and clamp it
            sampledCol /= superSamplingFactor * superSamplingFactor;
            sampledCol.clamp();
            img(x, y) = sampledCol ;
            
            // write loading bar 
            int barWidth = 50;
            std::cout << "[";
            int pos = barWidth * y/h;
            for (int i = 0; i < barWidth; ++i) {
              if (i < pos) std::cout << "-";
              else if (i == pos) std::cout << ">";
              else std::cout << " ";
            }
            std::cout << "] " << int(y/h * 100.0) << " %\r";
            std::cout.flush();
            
          }
      }
      std::cout << std::endl;
      
}

// --- Misc functions ----------------------------------------------------------

void Scene::setReflectionDepth(unsigned const &maxDepth) {
	std::cout << "Recursion depth: " << maxDepth << "\n";
	maxReflectionDepth = maxDepth;
}
void Scene::setSuperSamplingFactor(unsigned const &factor) {
	std::cout << "Super sampling factor: " << factor << "\n";
	superSamplingFactor = factor;	
}
void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

void Scene::setHasShadow(bool const &shadow)
{
    hasShadow = shadow;
}

void Scene::setToonShading(bool const &toon)
{
  hasToonShadingOn = toon;
}


unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}
