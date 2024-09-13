#include "enemyobject.h"

EnemyObject::EnemyObject()
{

}

EnemyObject::EnemyObject(float dx, float dy, float dz, float dr)
{
    Vertex v0{-0.2f,-1.4f,-0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v1{-0.2f, 0.4f, 0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v2{ 0.2f, 0.4f,-0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v3{-0.2f, 0.4f,-0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v4{ 0.2f,-1.4f, 0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v5{ 0.2f,-1.4f,-0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v6{-0.2f,-1.4f, 0.2f, 1.0f, 0.0f, 0.0f};
    Vertex v7{ 0.2f, 0.4f, 0.2f, 1.0f, 0.0f, 0.0f};

    mVertices.insert(mVertices.end(), {
                         v0, v1, v2,
                         v0, v3, v4,
                         v0, v0, v5,
                         v2, v5, v0,
                         v0, v1, v3,
                         v4, v6, v0,
                         v1, v6, v4,
                         v7, v5, v2,
                         v5, v7, v4,
                         v7, v2, v3,
                         v7, v3, v1,
                         v7, v1, v4
                     });

    mMatrix.setToIdentity();
    place(dx, dy, dz, dr);
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::init()
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

void EnemyObject::draw(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    glBindVertexArray(mVAO);
    glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, mMatrix.constData());

    switch (renderValue)
    {
    case 0:
        // Visible
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
        break;
    case 1:
        // Invisible
        glDrawArrays(GL_POINTS, 0, mVertices.size());
        break;
    default:
        break;
    }
}

void EnemyObject::place(float dx, float dy, float dz, float dr)
{
    mx += dx;
    my += dy;
    mz += dz;
    mr += dr;

//    qDebug() << "move";
    mMatrix.translate(dx, dy, dz);
}

float EnemyObject::getRadius()
{
    return mr;
}

QVector3D EnemyObject::getPosition()
{
    return mMatrix.column(3).toVector3D();
}

void EnemyObject::setPosition(float dx, float dy, float dz)
{
    mx += dx;
    my += dy;
    mz += dz;

    mMatrix.translate(dx, dy, dz);
}
