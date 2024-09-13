#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "visualobject.h"

class InteractiveObject : public VisualObject
{
public:
    InteractiveObject();
    InteractiveObject(std::string fileName, bool newObject);
    ~InteractiveObject() override;

    void init() override;
    void draw(GLint matrixUniform) override;
    void move(float x, float y, float z) override;

    void writeFile(std::string filnavn);
    void readFile(std::string filnavn);

    void findNormal();
    void findUV();

    float getRadius() override;
    QVector3D getPosition() override;
private:
    float mx, my, mz, mr;   //posisjon & radius
};

#endif // INTERACTIVEOBJECT_H
