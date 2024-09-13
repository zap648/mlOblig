#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "visualobject.h"

class Cube : public VisualObject
{
private:

public:
    Cube();
    ~Cube();

    bool mRotate{true};

    void init() override;
    void draw(GLint matrixUniform) override;
};

#endif // CUBE_H
