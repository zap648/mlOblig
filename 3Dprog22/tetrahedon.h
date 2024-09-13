#ifndef TETRAHEDON_H
#define TETRAHEDON_H

#include <vector>
#include "visualobject.h"

class Tetrahedon : public VisualObject
{
public:
    Tetrahedon();
    ~Tetrahedon();

    bool mRotate{true};

    void init() override;
    void draw(GLint matrixUniform) override;
};

#endif // TETRAHEDON_H
