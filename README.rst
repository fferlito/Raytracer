Raytracer 
==============

This *Raytracer* program is made for the course *Computer Graphics* at the Univesity of Groningen. It currently supports the Full Phong Lighting Model, shadows, reflections, textures, super sampling and a Cel-shader (a.k.a. Toon-shader). The objects supported are:
+ sphere
+ triangle
+ quad
+ plane
+ cylinder (with caps)


The project is organized as follows:

Code
  Contains the code used in the program itself: the code creates a PNG file with the chosen scene. 
  
Scenes
  Folder containing the JSON files with the scenes' description.  

Screenshots
  A folder with some pictures of the raytracer in action. 


Compiling the Raytracer
---------------------------
To compile the app in Android Studio, it's necessary to compile CLIPS first (it should be already compiled anyway). 
Follow the following steps to compile the CLIPS module, written in C:

*Compiling CLIPS from Android Studio*
 1. "*cd*" to the build directory
 2. use the command: "*cmake* .." 
 3. if step 3 is successful, compile the code using make -j# (where # is the number of cores in the CPU)
 4. to run it, you use "./ray <path to .json file> [output.png]".
