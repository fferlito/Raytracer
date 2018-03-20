We implemented the intersection function of the sphere where we calculate the intersection and the normal. Furthermore in scene.cpp we modified the trace function to implement phong diffuse ambient and specular shading. 

We added support for the triangle, plane and quad shape in raytracing.cpp and corresponding classes for these with their own intersection and normal calculations. 
We added an extra scene (scene03.json) that shows these new shapes.

Lastly we also added support for mesh loading, where everything is defined in terms of triangles (the coordinates for this need to be positive or moved to be positive programmaticaly).
We added a scene (scene04.json that shows the mesh.

To run the program you first need to cd to the build directory and use the command: cmake .. 

If this is succesful you compile it using make and then to run it you use ./ray <path to .json file> [output .png file].

In the build directory this would be ./ray ../Scenes/scene01.json for example. 
