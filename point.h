#ifndef POINT_H
#define POINT_H

#include "visualobject.h"

class Point : public VisualObject
{
public:
    Point();
    ~Point();

    bool mRotate{true};

    void init() override;
    void draw(GLint matrixUniform) override;
};

#endif // POINT_H
