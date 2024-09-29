#include <iostream>
#include <sstream>
#include "octaball.h"


//! \param n - the recursion level (default is 0 which makes the original Octahedron)
//!
//! The number of (duplicated) vertices are calculated based on the parameter n - the recursion level.
//! Initially we have 8 triangles, each with 3 vertices.
//! A subdivision consists of
//! - compute the midpoint of each edge in a triangel
//! - add these midpoint as vertices
//! - make three new edges by connecting new vertices
//! - preserve orientation
//! - move the three new points on the unit ball's surface by normalizing. Remember the vertex vector
//! is also a normal to the ball's surface.
//! The formula for the number of vertices is
//! m_nVertices = 3 * 8 * 4^n
//! where
//! - 3 comes from the number of vertices in a triangle,
//! - 8 comes from the original number of triangles in a regular Octahedron
//! - n is the recursion level (number of repeated subdivisions)
//!

OctaBall::OctaBall(int n, float r) : m_rekursjoner(n), m_indeks(0), PhysicsObject()
{
   mVertices.reserve(3 * 8 * pow(4, m_rekursjoner));
   setRadius(r);
   oktaederUnitBall();
   setAcceleration(QVector3D{0, -0.0001f /* "tyngdekraft" */, 0});
   setVelocity(QVector3D{-0.001f, 0.0f, -0.001f});
}

//!//! \brief OctaBall::~OctaBall() virtual destructor
//!
OctaBall::~OctaBall()
{
   //
}


// Parametrar inn: xyz koordinatane til eit triangel v1, v2, v3 ccw
// Bevarer orienteringa av hjørna
//!
//! \brief OctaBall::lagTriangel()
//! \param v1 - position on the unit ball for vertex 1
//! \param v2 - position on the unit ball for vertex 2
//! \param v3 - position on the unit ball for vertex 3
//!
//! lagTriangel() creates vertex data for a triangle's 3 vertices. This is done in the
//! final step of recursion.
//!
void OctaBall::lagTriangel(const QVector3D& v1, const QVector3D& v2,
const QVector3D& v3)
{
    Vertex v{v1.x(), v1.y(), v1.z(), 0, 0, 0.75f};
    mVertices.push_back(v);
    v = Vertex{v2.x(), v2.y(), v2.z(), 0, 0, 0.75f};
    mVertices.push_back(v);
    v = Vertex{v3.x(), v3.y(), v3.z(), 0, 0, 0.75f};
    mVertices.push_back(v);
 }


 // Rekursiv subdivisjon av triangel
 //!
 //! \brief OctaBall::subDivide() recursive subdivision of a triangel
 //! \param a coordinates for vertex a
 //! \param b coordinates for vertex b
 //! \param c coordinates for vertex c
 //! \param n level of recursion
 //!
 //! The function tests
 //! (if n>0)
 //! - three new edge midpoints are computed and normalized,
 //! - four new calls to subDivide() is done - one for each new triangle, preserving orientation
 //! and with decreased parameter n
 //! else
 //! - call lagTriangel(a, b, c)
 //!
 void OctaBall::subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n)
 {
    if (n>0) {
        QVector3D v1 = a+b; v1.normalize();
        QVector3D v2 = a+c; v2.normalize();
        QVector3D v3 = c+b; v3.normalize();
        subDivide(a, v1, v2, n-1);
        subDivide(c, v2, v3, n-1);
        subDivide(b, v3, v1, n-1);
        subDivide(v3, v2, v1, n-1);
    } else {
        lagTriangel(a * getRadius(), b * getRadius(), c * getRadius());
    }
 }


 //!
 //! \brief OctaBall::oktaederUnitBall() creates 8 unit ball vertices and call subDivide()
 //!
 //! If the parameter n of the constructor OctaBall() is zero, the result will be the
 //! original octa consisting of 8 triangles with duplicated vertices.
 //!
 void OctaBall::oktaederUnitBall()
 {
    QVector3D v0{0, 0, 1};
    QVector3D v1{1, 0, 0};
    QVector3D v2{0, 1, 0};
    QVector3D v3{-1, 0, 0};
    QVector3D v4{0, -1, 0};
    QVector3D v5{0, 0, -1};


    subDivide(v0, v1, v2, m_rekursjoner);
    subDivide(v0, v2, v3, m_rekursjoner);
    subDivide(v0, v3, v4, m_rekursjoner);
    subDivide(v0, v4, v1, m_rekursjoner);
    subDivide(v5, v2, v1, m_rekursjoner);
    subDivide(v5, v3, v2, m_rekursjoner);
    subDivide(v5, v4, v3, m_rekursjoner);
    subDivide(v5, v1, v4, m_rekursjoner);
 }


 //!
 //! \brief OctaBall::initVertexBufferObjects() calls glGenBuffers(), glBindBuffer() and glBufferdata()
 //! for using later use of glDrawArrays()
 //!
 void OctaBall::init()
 {
    initializeOpenGLFunctions();


    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );


    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );


    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );


    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);


    glBindVertexArray(0);
 }


 //!
 //! \brief OctaBall::draw() draws a ball using glDrawArrays()
 //! \param positionAttribute    vertex shader variable for position
 //! \param normalAttribute      vertex shader variable for normal or color
 //! \param textureAttribute     vertex shader variable for texture coordinates (optional)
 //!
 //! draw()
 //! - glBindBuffer()
 //! - glVertexAttribPointer()
 //! - glBindTexture()
 //! - glVertexAttribPointer()
 //! - glDrawArrays() with GL_TRIANGLES
 //!
 void OctaBall::draw(GLint matrixUniform)
 {
     mMatrixUniform = matrixUniform;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());//mVertices.size());

    //just to make the triangle rotate - tweak this:
    //                   degree, x,   y,   z -axis
//    if(mRotate)
//        mMatrix.rotate(2.f, 0.f, 1.0, 0.f);

    UpdatePosition();
 }

 int OctaBall::type()
 {
     return 1;
 }
