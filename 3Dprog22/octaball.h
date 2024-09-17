#ifndef OCTABALL_H
#define OCTABALL_H

#include "physicsobject.h"

class OctaBall : public PhysicsObject
{
private:
    int m_rekursjoner;
    int m_indeks;               // brukes i rekursjon, til å bygge m_vertices
    float radius;
    void lagTriangel(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
    void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);
    void oktaederUnitBall();
public:
    OctaBall(int n=0, float r=1);
    ~OctaBall();
    void init();
    void draw(GLint matrixUniform);
};

#endif // OCTABALL_H
