Raytracer and DNA double helix scene generator
==============================================

![frist](/Scenes/dna/dnaHD.png)  

This *Raytracer* program is made for the course *Computer Graphics* at the Univesity of Groningen. It currently supports:
+ Full Phong Lighting Model 
+ shadows 
+ reflections 
+ textures 
+ super sampling 
+ Cel-shader (a.k.a. Toon-shader)
+ Gooch shader

The objects supported are:
+ sphere
+ triangle
+ quad
+ plane
+ cylinder (with caps)
+ triangle meshes 


The project is organized as follows:
-----------------------------------

*Code*:
  Contains the code used in the program itself: the code creates a PNG file with the chosen scene. 
  
*Scenes*:
  Folder containing the JSON files with the scenes' description.  

*Screenshots*:
  A folder with some pictures of the raytracer in action. 

*Models*:
  contains various meshed saved as *.obj* files. Shapes are defined with triangular patches. 

*GenerateDNA*:
  Contains the code written in C used to generate the JSON file of the DNA double helix shown above. Read the related *README* file to get insights.

Compiling the Raytracer
---------------------------
To compile the code in Linux, follow this instructions:

 1. "*cd*" to the build directory
 2. use the command: "*cmake* .." 
 3. if step 3 is successful, compile the code using make -j# (where # is the number of cores in the CPU)
 4. to run it, you use "./ray <path to .json file> [output.png]".
  

Screenshots
---------------------------
DNA with Phong lighting and reflections
![frist](/Scenes/dna/dnaRef.png) 

DNA with Gooch lighting model
![frist](/Scenes/dna/dnaGooch.png) 

DNA with cell shading model
![frist](/Scenes/dna/dnaToon.png) 

![frist](/Screenshots/toon.png) 
![frist](/Screenshots/cyl.png) 
