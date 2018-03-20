#ifndef VERTEX_H_
#define VERTEX_H_

struct Vertex
{
    float x;    // x coordinate
    float y;    // y coordinate
    float z;    // z coordinate
    float nx;   // x component of normal
    float ny;   // y component of normal
    float nz;   // z component of normal
    float u;    // u (or s) coordinate of texture
    float v;    // v (or t) coordinate of texture
};

#endif
