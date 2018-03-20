#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* This script creates an object for the raytracer containing one molecule of H2O.
*   The input is the xyz position of the central atom sphere (Oxygen).
*   The code will generate the two other atom spheres and their 
*   cylindric bounds using random vectors 
*/


void  getRandomNormal(float *normal){

  int max = 100;
  int min = 0;
  float a = (rand() % (max + 1 - min) + min);
  a /= max;
  a = a*2 -1;
  normal[0] = a;
  a = (rand() % (max + 1 - min) + min);
  a /= max;
  a = a*2 -1;
  normal[1] = a;

  a = (rand() % (max + 1 - min) + min);
  a /= max;
  a = a*2 -1;
  normal[2] = a;
  
  
  return;
  
}

int main(int arcg, char *argv[]){
  
  // initiate random function using time
  srand ( time(NULL) );

  // position oxygen
  int oPosition[3];
  scanf("%d %d %d", &oPosition[0], &oPosition[1], &oPosition[2]);
  

  //-----------------------------------------------//
  // DEFINE VARIABLES OF H2O molecule (three sphere + 2 bounds)
  int rO = 6;                             // radius of oxigen
  int rH = 4;
  int spacingAtoms = 18;                  // space sampling between bases: (34 Angstrom)
  int radiusCylinder = 2;                 // radius of the cylinders (the 4 bases)
  float oxygenColor[3] = {1.0,0,0}; 
  float hidrogenColor2[3] = {0.635, 0.858, 0.905};
  float boundColor[3] = {0.760, 0.760, 0.760}; 
  

  // red sphere
  printf("          { \n");
  printf("              \"type\": \"sphere\",\n");
  printf("              \"comment\": \"Oxygen sphere (H2O)\",\n");
  printf("              \"position\": [%d, %d, %d],\n", oPosition[0], oPosition[1], oPosition[2]);
  printf("              \"radius\": %d,\n", rO);
  printf("              \"material\":\n");
  printf("              {\n");
  printf("                  \"color\": [%lf, %lf, %lf],\n",oxygenColor[0], oxygenColor[1], oxygenColor[2]);
  printf("                  \"ka\": 0.2,\n");
  printf("                  \"kd\": 0.6,\n");
  printf("                  \"ks\": 0.8,\n");
  printf("                  \"n\": 64\n");
  printf("              }\n");
  printf("          },\n");
  
  
  // find position of the two hidrogen spheres given the normals of their bounds and its lenght
  float normal1[3];
  getRandomNormal(normal1);
  float normal2[3];
  getRandomNormal(normal2);

  int h1Position[3];
  int h2Position[3];
  
  h1Position[0] = spacingAtoms / sqrt(normal1[0] * normal1[0] + normal1[1] * normal1[1] + normal1[2] * normal1[2]) * normal1[0] + oPosition[0];
  h1Position[1] = spacingAtoms / sqrt(normal1[0] * normal1[0] + normal1[1] * normal1[1] + normal1[2] * normal1[2]) * normal1[1] + oPosition[1];
  h1Position[2] = spacingAtoms / sqrt(normal1[0] * normal1[0] + normal1[1] * normal1[1] + normal1[2] * normal1[2]) * normal1[2] + oPosition[2];
  
  h2Position[0] = spacingAtoms / sqrt(normal2[0] * normal2[0] + normal2[1] * normal2[1] + normal2[2] * normal2[2]) * normal2[0] + oPosition[0];
  h2Position[1] = spacingAtoms / sqrt(normal2[0] * normal2[0] + normal2[1] * normal2[1] + normal2[2] * normal2[2]) * normal2[1] + oPosition[1];
  h2Position[2] = spacingAtoms / sqrt(normal2[0] * normal2[0] + normal2[1] * normal2[1] + normal2[2] * normal2[2]) * normal2[2] + oPosition[2];
  
  printf("          { \n");
  printf("              \"type\": \"sphere\",\n");
  printf("              \"comment\": \"Hydrogen sphere\",\n");
  printf("              \"position\": [%d, %d, %d],\n", h2Position[0], h2Position[1], h2Position[2]);
  printf("              \"radius\": %d,\n", rH);
  printf("              \"material\":\n");
  printf("              {\n");
  printf("                  \"color\": [%lf, %lf, %lf],\n", hidrogenColor2[0], hidrogenColor2[1], hidrogenColor2[2]);
  printf("                  \"ka\": 0.2,\n");
  printf("                  \"kd\": 0.7,\n");
  printf("                  \"ks\": 0.8,\n");
  printf("                  \"n\": 64\n");
  printf("              }\n");
  printf("          },\n");
  
  printf("          { \n");
  printf("              \"type\": \"sphere\",\n");
  printf("              \"comment\": \"Hydrogen sphere\",\n");
  printf("              \"position\": [%d, %d, %d],\n", h1Position[0], h1Position[1], h1Position[2]);
  printf("              \"radius\": %d,\n", rH);
  printf("              \"material\":\n");
  printf("              {\n");
  printf("                  \"color\": [%lf, %lf, %lf],\n", hidrogenColor2[0], hidrogenColor2[1], hidrogenColor2[2]);
  printf("                  \"ka\": 0.2,\n");
  printf("                  \"kd\": 0.7,\n");
  printf("                  \"ks\": 0.8,\n");
  printf("                  \"n\": 64\n");
  printf("              }\n");
  printf("          },\n");

     

  // add two cylinders    
  printf("          { \n");
  printf("              \"type\": \"cylinder\",\n");
  printf("              \"comment\": \"cylinder\",\n");
  printf("              \"origin\": [%d, %d, %d],\n", oPosition[0], oPosition[1], oPosition[2]);
  printf("              \"axis\": [%lf, %lf, %lf],\n", normal1[0], normal1[1], normal1[2]);
  printf("              \"radius\": %d,\n", radiusCylinder);
  printf("              \"height\": %d,\n", spacingAtoms);
  printf("              \"material\":\n");
  printf("              {\n");
  printf("                  \"color\": [%lf, %lf, %lf],\n", boundColor[0], boundColor[1], boundColor[2]);
  printf("                  \"ka\": 0.2,\n");
  printf("                  \"kd\": 0.7,\n");
  printf("                  \"ks\": 0.5,\n");
  printf("                  \"n\": 64\n");
  printf("              }\n");
  printf("          },\n");
  
  printf("          { \n");
  printf("              \"type\": \"cylinder\",\n");
  printf("              \"comment\": \"cylinder (spiral)\",\n");
  printf("              \"origin\": [%d, %d, %d],\n", oPosition[0], oPosition[1], oPosition[2]);
  printf("              \"axis\": [%lf, %lf, %lf],\n", normal2[0], normal2[1], normal2[2]);
  printf("              \"radius\": %d,\n", radiusCylinder);
  printf("              \"height\": %d,\n", spacingAtoms);
  printf("              \"material\":\n");
  printf("              {\n");
  printf("                  \"color\": [%lf, %lf, %lf],\n", boundColor[0], boundColor[1], boundColor[2]);
  printf("                  \"ka\": 0.2,\n");
  printf("                  \"kd\": 0.7,\n");
  printf("                  \"ks\": 0.5,\n");
  printf("                  \"n\": 64\n");
  printf("              }\n");
  printf("          },\n");
      
  
  return 0;
}
