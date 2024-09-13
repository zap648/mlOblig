#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "visualobject.h"

class Triangle : public VisualObject
{
public:
    Triangle();
    Triangle(Vertex v0, Vertex v1, Vertex v2);
    ~Triangle();

protected:
    std::vector<Triangle> mTriangles;
};

#endif // TRIANGLE_H
