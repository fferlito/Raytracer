#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


enum colors {RED_GUANINE, 
            BLU_CYTOSINE,   
            GREEN_TYMINE, 
            YELLOW_ACTINE};


float distanceBetweenPoints(int x, int y, int z, int x2, int  y2, int z2){
  double distance = sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2) + (z-z2)*(z-z2));
  return distance;
}

void  getRandomColorBase(float *baseColor, float *baseColor2){
  int max = 3;
  int min = 0;
  int randomColor = rand() % (max + 1 - min) + min;
  
  switch(randomColor){
    case RED_GUANINE:
      baseColor[0] = 1;
      baseColor[1] = 0;
      baseColor[2] = 0;
      
      baseColor2[0] = 0;
      baseColor2[1] = 0;
      baseColor2[2] = 1;      
      return ;
      break;
    case BLU_CYTOSINE:
      baseColor[0] = 0;
      baseColor[1] = 0;
      baseColor[2] = 1;
      
      baseColor2[0] = 1;
      baseColor2[1] = 0;
      baseColor2[2] = 0;
      return;
      break;
    case GREEN_TYMINE:
      baseColor[0] = 0;
      baseColor[1] = 1;
      baseColor[2] = 0;
      
      baseColor2[0] = 1;
      baseColor2[1] = 0.8;
      baseColor2[2] = 0;
      return;
      break;
    case YELLOW_ACTINE:
      baseColor[0] = 1;
      baseColor[1] = 0.8;
      baseColor[2] = 0;
      
      baseColor2[0] = 0;
      baseColor2[1] = 1;
      baseColor2[2] = 0;
      return;
      break;
    default:
      baseColor[0] = 1;
      baseColor[1] = 1;
      baseColor[2] = 1;
      
      baseColor2[0] = 1;
      baseColor2[1] = 0;
      baseColor2[2] = 1;
      return;
      break;
  }
}


int main(int arcg, char *argv[]){
  
  //----------------------------------------------//
  // Insert start and end limits i.e. horizontal spiral = (left border, right border) 
  int upLimit;
  scanf("%d", &upLimit);
  
  // horizontal spiral origin, from left side to right: (0, height/2, 100)
  int xPos;
  int yPos;
  int zPos;
  scanf("%d %d %d", &xPos, &yPos, &zPos);
  
  
  //-----------------------------------------------//
  // DEFINE VARIABLES OF DNA SPIRAL
  int R = 60;                             // radius of DNA
  int spacingAtoms = 20;                  // space sampling between bases: (34 Angstrom)
  int radiusSphere = 10;                  // radaius of atoms in double helix
  int radiusCylinder = 1;                 // radius of the cylinders (the 4 bases)
  double colorBackground[3] = {0.243, 0, 0.356};
  
  // DEFINE SCENE LIGHTS AND SPECIFICS
  printf("{\n");
  printf("      \"Eye\": [200, 200, 1000],\n");
  printf("      \"Shadows\": true,\n");
  printf("      \"MaxRecursionDepth\": 0,\n");
  printf("      \"SuperSamplingFactor\": 2,\n");
  printf("      \"Lights\": [\n");
  printf("          {\n");
  printf("              \"position\": [-200, 600, 1500],\n");
  printf("              \"color\": [1.0, 1.0, 1.0]\n");
  printf("          }\n");
  printf("      ],\n");
  printf("      \"Objects\": [\n");

    
    // GENERATE SPIRAL OBJECTS (1 red ball and 1 blue ball per iteration)
  int x;
  for(float t = 0; x < upLimit; t = t + 0.25){
    
    x = t*spacingAtoms + xPos;
    int z = R * cos(t) + zPos;
    int y = R * sin(t) + yPos;
    
    // red sphere
    printf("          { \n");
    printf("              \"type\": \"sphere\",\n");
    printf("              \"comment\": \"Red sphere (spiral)\",\n");
    printf("              \"position\": [%d, %d, %d],\n", x, y, z);
    printf("              \"radius\": %d,\n", radiusSphere);
    printf("              \"material\":\n");
    printf("              {\n");
    printf("                  \"color\": [1.0, 0.0, 0.0],\n");
    printf("                  \"ka\": 0.2,\n");
    printf("                  \"kd\": 0.7,\n");
    printf("                  \"ks\": 0.5,\n");
    printf("                  \"n\": 64\n");
    printf("              }\n");
    printf("          },\n");
  
    
        // blue sphere
    int x2 = t*spacingAtoms + xPos;
    int z2 = (R * -cos(t) + zPos) ;
    int y2 = (R * sin(t) * (-1) + yPos);
      
    printf("          { \n");
    printf("              \"type\": \"sphere\",\n");
    printf("              \"comment\": \"Blue sphere (spiral)\",\n");
    printf("              \"position\": [%d, %d, %d],\n", x2, y2, z2);
    printf("              \"radius\": %d,\n", radiusSphere);
    printf("              \"material\":\n");
    printf("              {\n");
    printf("                  \"color\": [0.0, 0.0, 1.0],\n");
    printf("                  \"ka\": 0.2,\n");
    printf("                  \"kd\": 0.7,\n");
    printf("                  \"ks\": 0.5,\n");
    printf("                  \"n\": 64\n");
    printf("              }\n");
    printf("          },\n");

    
    // pick the color of a random base and of its Watson and Crick complementary base
    // tymine  <-> actine 
    // guanine <-> cytosine
    float baseColor[3]; 
    float baseColor2[3]; 
    getRandomColorBase(baseColor, baseColor2);

    // add two cylinders in the middle of the helix    
    printf("          { \n");
    printf("              \"type\": \"cylinder\",\n");
    printf("              \"comment\": \"Green cylinder (spiral)\",\n");
    printf("              \"origin\": [%d, %d, %d],\n", x, y, z);
    printf("              \"axis\": [%d, %d, %d],\n", x2-x, y2-y, z2-z);
    printf("              \"radius\": %d,\n", radiusCylinder);
    printf("              \"height\": %lf,\n", distanceBetweenPoints(x, y, z, x2, y2, z2)/2);
    printf("              \"material\":\n");
    printf("              {\n");
    printf("                  \"color\": [%lf, %lf, %lf],\n", baseColor[0], baseColor[1], baseColor[2]);
    printf("                  \"ka\": 0.2,\n");
    printf("                  \"kd\": 0.7,\n");
    printf("                  \"ks\": 0.5,\n");
    printf("                  \"n\": 64\n");
    printf("              }\n");
    printf("          },\n");
    printf("          { \n");
    printf("              \"type\": \"cylinder\",\n");
    printf("              \"comment\": \"Green cylinder (spiral)\",\n");
    printf("              \"origin\": [%d, %d, %d],\n", x2, y2, z2);
    printf("              \"axis\": [%d, %d, %d],\n", x - x2, y - y2, z - z2);
    printf("              \"radius\": %d,\n", radiusCylinder);
    printf("              \"height\": %lf,\n", distanceBetweenPoints(x, y, z, x2, y2, z2)/2);
    printf("              \"material\":\n");
    printf("              {\n");
    printf("                  \"color\": [%lf, %lf, %lf],\n", baseColor2[0], baseColor2[1], baseColor2[2]);
    printf("                  \"ka\": 0.2,\n");
    printf("                  \"kd\": 0.7,\n");
    printf("                  \"ks\": 0.5,\n");
    printf("                  \"n\": 64\n");
    printf("              }\n");
    printf("          },\n");
      
  }
  
  // Grey background (a huge grey sphere)
  printf("          { \n");
  printf("              \"type\": \"sphere\",\n");
  printf("              \"comment\": \"Grey sphere (background)\",\n");
  printf("              \"position\": [800, 400, -4000],\n");
  printf("              \"radius\": 4000,\n");
  printf("              \"material\":\n");
  printf("              {\n");
  printf("                  \"color\": [%lf, %lf, %lf],\n", colorBackground[0], colorBackground[1], colorBackground[2]);
  printf("                  \"ka\": 0.2,\n");
  printf("                  \"kd\": 0.8,\n");
  printf("                  \"ks\": 0,\n");
  printf("                  \"n\": 64\n");
  printf("              }\n");
  printf("          }\n");
  printf("      ]\n");
  printf("}\n");

  
  return 0;
}
