#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include "visualobject.h"

class TriangleSurface : public VisualObject
{
public:
    TriangleSurface();
    TriangleSurface(std::string filnavn);
    ~TriangleSurface();

    bool mRotate{true};

    void readFile(std::string filnavn);
    void init() override;
    void draw(GLint matrixUniform) override;
};

#endif // TRIANGLESURFACE_H
