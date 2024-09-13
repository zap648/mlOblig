#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <fstream>

struct Vertex {
    // Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    // Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);

    float m_xyz[3];     // Position in 3D
    float m_normal[3];  // Normal in 3D/RGB colours
    float m_st[2];      // Texture Coordinates if used

    Vertex();
    Vertex(float x, float y, float z, float r, float g, float b);
    Vertex(float x, float y, float z, float r, float g, float b, float s, float t);
};
#endif // VERTEX_H
