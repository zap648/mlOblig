#include "triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
{
    mVertices.insert(mVertices.end(),
                     {
                         v0, v1, v2
                     });

    // OBS! Vertices MUST be drawn clockwise from the light source's perspective to get the correct normal
    QVector3D normal = VisualObject::getVectorNormal(v0, v2, v1);

    v0.m_normal[0] = normal.x();
    v0.m_normal[1] = normal.y();
    v0.m_normal[2] = normal.z();

    v1.m_normal[0] = normal.x();
    v1.m_normal[1] = normal.y();
    v1.m_normal[2] = normal.z();

    v2.m_normal[0] = normal.x();
    v2.m_normal[1] = normal.y();
    v2.m_normal[2] = normal.z();
}
