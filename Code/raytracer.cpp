#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/sphere.h"
#include "shapes/triangle.h"
#include "shapes/plane.h"
#include "shapes/quad.h"
#include "shapes/cylinder.h"


// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"
#include "objloader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;        // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node)
{
    ObjectPtr obj = nullptr;

// =============================================================================
// -- Determine type and parse object parametrers ------------------------------
// =============================================================================

    if (node["type"] == "sphere")
    {
        Point pos(node["position"]);
        double radius = node["radius"];
        // Check if the sphere contains a rotation
        if (node.find("rotation") != node.end() && node.find("angle") != node.end()) {
			Vector rotation(node["rotation"]);
			rotation = rotation.normalized();
			double angle = node["angle"];
			obj = ObjectPtr(new Sphere(pos, radius, rotation, angle));
		}
		else {
			obj = ObjectPtr(new Sphere(pos, radius));
		}
    }
    else if (node["type"] == "triangle") {
		Point v0(node["vertex0"]);
		Point v1(node["vertex1"]);
		Point v2(node["vertex2"]);
		obj = ObjectPtr(new Triangle(v0, v1, v2));
	}
	else if (node["type"] == "plane") {
		obj = ObjectPtr(new Plane(node["a"], node["b"], node["c"], node["d"]));
	}
	else if (node["type"] == "quad") {
		Point v0(node["vertex0"]);
		Point v1(node["vertex1"]);
		Point v2(node["vertex2"]);
		Point v3(node["vertex3"]);
		obj = ObjectPtr(new Quad(v0, v1, v2, v3));
	}	
	else if (node["type"] == "cylinder") {
		Point v0(node["origin"]);
		Point v1(node["axis"]);
        double v2 = node["height"];
		double v3 = node["radius"];
		obj = ObjectPtr(new Cylinder(v0, v1, v2, v3));
	}
	else if (node["type"] == "mesh") {
		
		//Load the data of the mesh
		string s = node["object"];
		OBJLoader mesh(s);
		vector<Vertex> data = mesh.vertex_data();
		//Load the material of the mesh
		Material material = parseMaterialNode(node["material"]);
		
		//Add every triangle of the mesh to the scene
		for (unsigned i = 0; i < data.size(); i += 3) {
			Vertex vertex0 = data[i];
			Vertex vertex1 = data[i+1];
			Vertex vertex2 = data[i+2];
			
			// The shift is needed for when there are negative coordinates so it is displayed in the 400x400 window
			double y_shift = 200;
			double x_shift = 100;
			
			Point v0(vertex0.x+x_shift, vertex0.y+y_shift, vertex0.z);
			Point v1(vertex1.x+x_shift, vertex1.y+y_shift, vertex1.z);
			Point v2(vertex2.x+x_shift, vertex2.y+y_shift, vertex2.z);
			obj = ObjectPtr(new Triangle(v0, v1, v2));
			obj->material = material;
			scene.addObject(obj);
		}
		return true;
	}
    else
    {
        cerr << "Unknown object type: " << node["type"] << ".\n";
    }

// =============================================================================
// -- End of object reading ----------------------------------------------------
// =============================================================================

    if (!obj)
        return false;

    // Parse material and add object to the scene
    obj->material = parseMaterialNode(node["material"]);

    scene.addObject(obj);
    return true;
}

Light Raytracer::parseLightNode(json const &node) const
{
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const
{
	double ka = node["ka"];
    double kd = node["kd"];
    double ks = node["ks"];
    double n  = node["n"];
   
	// See if the material uses a color or a texture and use the appropiate initializer
	if (node.find("color") != node.end()) {
		// node color found
		Color col(node["color"]);
		return Material(col, ka, kd, ks, n);
	}
	else {
		// Material uses texture as no color was given
		std::cout << "Using texture at path: "<< "../Scenes/" << node["texture"] << "\n";
		std::string textureName = node["texture"];
		Image texture("../Scenes/"+textureName);
	    return Material(texture, ka, kd, ks, n);
	}
}

bool Raytracer::readScene(string const &ifname)
try
{
    // Read and parse input json file
    ifstream infile(ifname);
    if (!infile) throw runtime_error("Could not open input file for reading.");
    json jsonscene;
    infile >> jsonscene;

// =============================================================================
// -- Read your scene data in this section -------------------------------------
// =============================================================================

    std::cout << "Loading scene...\n";
    Point eye(jsonscene["Eye"]);
    scene.setEye(eye);

    // TODO: add your other configuration settings here
   
   
   // Check if there is a shadow variable
    if (jsonscene["Shadows"] == false || jsonscene["Shadows"] == true) {
		scene.setHasShadow(jsonscene["Shadows"]);
		std::cout << "Shadow is " << jsonscene["Shadows"] << "\n";
	}
	else {
		std::cout << "Shadow: false (not defined)" << "\n";
	    scene.setHasShadow(false);
	}
	   // Check if there is a shadow variable
    if (jsonscene["Toon"] == false || jsonscene["Toon"] == true) {
		scene.setToonShading(jsonscene["Toon"]);
		std::cout << "Toon shading:" << jsonscene["Shadows"] << "\n";
	}
	else {
		std::cout << "Toon shading: false (not defined)" << "\n";
	    scene.setToonShading(false);
	}
	// Check for a recursion depth variable
	if (jsonscene["MaxRecursionDepth"] >= 0) {
		scene.setReflectionDepth(jsonscene["MaxRecursionDepth"]);
	}
	else {
		scene.setReflectionDepth(0);
	}
	// check for a sampling factor
	if (jsonscene["SuperSamplingFactor"] > 1) {
		scene.setSuperSamplingFactor(jsonscene["SuperSamplingFactor"]);
	}
	else {
		scene.setSuperSamplingFactor(1);
	}
	
    for (auto const &lightNode : jsonscene["Lights"])
        scene.addLight(parseLightNode(lightNode));

    unsigned objCount = 0;
    for (auto const &objectNode : jsonscene["Objects"])
        if (parseObjectNode(objectNode))
            ++objCount;

    cout << "Parsed " << objCount << " objects.\n";

// =============================================================================
// -- End of scene data reading ------------------------------------------------
// =============================================================================

    return true;
}
catch (exception const &ex)
{
    cerr << ex.what() << '\n';
    return false;
}

void Raytracer::renderToFile(string const &ofname)
{
    // TODO: the size may be a settings in your file
    Image img(800, 400);
    cout << "\nTracing...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}
