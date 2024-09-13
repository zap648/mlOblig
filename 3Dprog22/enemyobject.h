#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "visualobject.h"

class EnemyObject : public VisualObject
{
public:
    EnemyObject();
    EnemyObject(float dx, float dy, float dz, float dr);
    ~EnemyObject();

    void init() override;
    void draw(GLint matrixUniform) override;
    void place(float dx, float dy, float dz, float dr);
    QVector3D getPosition() override;
    float getRadius() override;

    void setPosition(float dx, float dy, float dz);
private:

    QVector3D position;
    float mx, my, mz, mr;  //posisjon
};

#endif // ENEMYOBJECT_H
