#include "trianglesurface.h"

TriangleSurface::TriangleSurface()
{
    // Required Vertices
    //     v   x     y     z     r     g     b
    Vertex v0{ 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex v1{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex v2{ 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex v3{ 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f};

    // Surface quad_1/2
    mVertices.push_back(v0);
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    // Surface quad_2/2
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);

    mMatrix.setToIdentity();
}

TriangleSurface::TriangleSurface(std::string filnavn)
{

}

TriangleSurface::~TriangleSurface()
{

}

void TriangleSurface::readFile(std::string filnavn)
{

}

void TriangleSurface::init()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 mVertices.size() * sizeof(Vertex),
                 mVertices.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void TriangleSurface::draw(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    glBindVertexArray(mVAO);
    glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    //just to make the triangle rotate - tweak this:
    //                   degree, x,   y,   z -axis
    if(mRotate)
        mMatrix.rotate(2.0f, 0.0f, 1.0f, 0.0f);
}
