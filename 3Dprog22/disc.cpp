#include "disc.h"

Disc::Disc()
{

}

Disc::Disc(std::string filnavn)
{

}

Disc::~Disc()
{

}

void Disc::readFile(std::string filnavn)
{

}

void Disc::writeFile(std::string filnavn)
{

}

void Disc::init()
{
    ///
    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

    // 1st attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //enable the matrixUniform
    //mMatrixuniform = glGetuniformLocation(matrixUniform, "matrix");
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Disc::draw(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    initializeOpenGLFunctions();
    glBindVertexArray(mVAO);
    //GL_FALSE for QMatrix4x4
    glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(GL_TRIANGLE_FAN, mVertices.size(), GL_UNSIGNED_INT, reinterpret_cast<const void*>(0)); //mVertices.size();
}

// Konstruer for  TRIANGLE_FAN her
// Hardkodet sektorstørrelse og antall
void Disc::construct()
{
    mVertices.push_back(Vertex{0,0,0,1,1,1});
    for (int i = 0; i < 13; i++)
    {
        double angle = 30 * i * M_PI / 180;
        qDebug() << "angle = " << angle;
        float x = cos(angle);
        float y = sin (angle);
        float z = 0.0f;
        float r = i % 2;
        float g = 0.f;
        float b = 0.5f;
        mVertices.push_back(Vertex{x,y,z,r,g,b});
    }
    for (GLuint i = 0; i < 14; i++)
        mIndices.push_back(i);
}

void Disc::move(float dt)
{
    float degrees = (180 * dt) / M_PI;
    mRotation.rotate(degrees, 0, 0, 1);
    mMatrix = mRotation;
}
