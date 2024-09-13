#ifndef TROPHYOBJECT_H
#define TROPHYOBJECT_H

#include "visualobject.h"

class TrophyObject : public VisualObject
{
public:
    TrophyObject();
    TrophyObject(float dx, float dy, float dz, float dr);
    ~TrophyObject() override;

    void init() override;
    void draw(GLint matrixUniform) override;
    void place(float dx, float dy, float dz, float dr);
    QVector3D getPosition() override;
    float getRadius() override;

private:
    /*
    struct {
        float mx, my, mz;
    } position;
    */
    QVector3D position;
    float mx, my, mz, mr;  //posisjon
};

#endif // TROPHYOBJECT_H
