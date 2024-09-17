#include "bouncybox.h"

BouncyBox::BouncyBox()
{


    p.push_back(new Plane(1.0f, 0.0f, 1.0f)); // Floor Plane
    p.back()->setPosition3D(QVector3D{0.0f, -0.5f, 0.0f});  // Puts the plane down
    p.push_back(new Plane(1.0f, 1.0f, 0.0f));   // Back Plane
    p.back()->setPosition3D(QVector3D{0.0f, 0.0f, 0.5f});     // Places the plane back
    p.push_back(new Plane(0.0f, 1.0f, 1.0f)); // Left Plane
    p.back()->setPosition3D(QVector3D{-0.5f, 0.0f, 0.0f});     // Places the plane left
    p.push_back(new Plane(1.0f, 1.0f, 0.0f));   // Front Plane
    p.back()->setPosition3D(QVector3D{0.0f, 0.0f, -0.5f});    // Places the plane forwards
    p.push_back(new Plane(0.0f, 1.0f, 1.0f)); // Right Plane
    p.back()->setPosition3D(QVector3D{0.5f, 0.0f, 0.0f});      // Places the plane right
    p.push_back(new Plane(1.0f, 0.0f, 1.0f)); // Roof Plane
    p.back()->setPosition3D(QVector3D{0.0f, 0.5f, 0.0f});     // Places the plane up
}

BouncyBox::BouncyBox(float width, float height, float length, bool roof)
{
    p.push_back(new Plane(width, 0.0f,   length)); // Floor Plane
    p.back()->setPosition3D(QVector3D{0.0f, - height / 2, 0.0f});   // Puts the plane down
    p.push_back(new Plane(width, height, 0.0f));   // Back Plane
    p.back()->setPosition3D(QVector3D{0.0f, 0.0f, length / 2});     // Places the plane back
    p.push_back(new Plane(0.0f,  height, length)); // Left Plane
    p.back()->setPosition3D(QVector3D{-width / 2, 0.0f, 0.0f});     // Places the plane left
    p.push_back(new Plane(width, height, 0.0f));   // Front Plane
    p.back()->setPosition3D(QVector3D{0.0f, 0.0f, -length / 2});    // Places the plane forwards
    p.push_back(new Plane(0.0f,  height, length)); // Right Plane
    p.back()->setPosition3D(QVector3D{width / 2, 0.0f, 0.0f});      // Places the plane right

    if (roof)
    {
        p.push_back(new Plane(width, 0.0f, length)); // Roof Plane
        p.back()->setPosition3D(QVector3D{0.0f, height / 2, 0.0f}); // Places the plane up
    }
}

BouncyBox::~BouncyBox()
{

}
