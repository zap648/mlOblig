#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <vector>
#include "visualobject.h"

class Tetrahedron : public VisualObject
{
public:
    Tetrahedron();
    Tetrahedron(float x, float y, float z, bool roof);
    ~Tetrahedron();

    bool mRotate{true};
    bool tRoof;

    void init() override;
    void draw(GLint matrixUniform) override;
};

#endif // TETRAHEDRON_H
