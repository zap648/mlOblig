#ifndef LIGHT_H
#define LIGHT_H

#include "visualobject.h"

///Simple Light class that has a small mesh and some light parameters
class Light : public VisualObject
{
public:
    ///Light class with mesh and light parameters
    Light();
    virtual void init() override;
    virtual void draw(GLint matrixUniform) override;

    GLfloat mAmbientStrength{0.3f};
    QVector3D mAmbientColor{0.3f, 0.3f, 0.3f};  //Grey

    GLfloat mLightStrength{0.7f};
    QVector3D mLightColor{0.3f, 0.9f, 0.3f};    //Green

    GLfloat mSpecularStrength{0.9f};
    GLint mSpecularExponent{4};

    QVector3D getPosition() override;

private:
    float mx, my, mz, mr;
};

#endif // LIGHT_H
