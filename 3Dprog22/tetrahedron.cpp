#include "tetrahedron.h"

Tetrahedron::Tetrahedron()
{
    // Tetrahedon
    // 1st Tri
    mVertices.push_back(Vertex{0,       0.5f,   0.25f,  1.0f,  0,  0});
    mVertices.push_back(Vertex{0,      -0.5f,   0.25f,  1.0f,  0,  0});
    mVertices.push_back(Vertex{0.5f,    0,     -0.25f,  0,  1.0f,  0});
    // 2nd Tri
    mVertices.push_back(Vertex{ 0,      0.5f,   0.25f,  1.0f,  0,  0});
    mVertices.push_back(Vertex{ 0,     -0.5f,   0.25f,  1.0f,  0,  0});
    mVertices.push_back(Vertex{-0.5f,   0,     -0.25f,  0,  0,  1.0f});
    // 3rd Tri
    mVertices.push_back(Vertex{ 0,      0.5f,   0.25f,  1.0f,  0,  0});
    mVertices.push_back(Vertex{ 0.5f,   0,     -0.25f,  0,  1.0f,  0});
    mVertices.push_back(Vertex{-0.5f,   0,     -0.25f,  0,  0,  1.0f});
    // 4th Tri
    mVertices.push_back(Vertex{ 0,     -0.5f,   0.25f,  1.0f,  0,  0});
    mVertices.push_back(Vertex{ 0.5f,   0,     -0.25f,  0,  1.0f,  0});
    mVertices.push_back(Vertex{-0.5f,   0,     -0.25f,  0,  0,  1.0f});
    mMatrix.setToIdentity();
}

Tetrahedron::Tetrahedron(float x, float y, float z, bool roof)
{
    // Tetrahedon
    // 1st Tri
    mVertices.push_back(Vertex{0 * x,   0.5f * y,   0.25f * z,  1.0f,  0,  0});
    mVertices.push_back(Vertex{0 * x,  -0.5f * y,   0.25f * z,  1.0f,  0,  0});
    mVertices.push_back(Vertex{0.5f * x,   0 * y,  -0.25f * z,  0,  1.0f,  0});
    // 2nd Tri
    mVertices.push_back(Vertex{ 0 * x,  0.5f * y,   0.25f * z,  1.0f,  0,  0});
    mVertices.push_back(Vertex{ 0 * x, -0.5f * y,   0.25f * z,  1.0f,  0,  0});
    mVertices.push_back(Vertex{-0.5f * x,  0 * y,  -0.25f * z,  0,  0,  1.0f});
    // 3rd Tri
    mVertices.push_back(Vertex{ 0 * x,  0.5f * y,   0.25f * z,  1.0f,  0,  0});
    mVertices.push_back(Vertex{ 0.5f * x,  0 * y,  -0.25f * z,  0,  1.0f,  0});
    mVertices.push_back(Vertex{-0.5f * x,  0 * y,  -0.25f * z,  0,  0,  1.0f});
    // 4th Tri
    mVertices.push_back(Vertex{ 0 * x, -0.5f * y,   0.25f * z,  1.0f,  0,  0});
    mVertices.push_back(Vertex{ 0.5f * x,  0 * y,  -0.25f * z,  0,  1.0f,  0});
    mVertices.push_back(Vertex{-0.5f * x,  0 * y,  -0.25f * z,  0,  0,  1.0f});
    tRoof = roof;
    mMatrix.setToIdentity();
}

Tetrahedron::~Tetrahedron()
{

}

void Tetrahedron::init()
{
    initializeOpenGLFunctions();

    //********************** Making the object to be drawn **********************

    //Making and using the Vertex Array Object - VAO
    //VAO is a containter that holds VBOs
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Making and using the Vertex Buffer Object to hold vertices - VBO
    //Since the mVAO is bound, this VBO will belong to that VAO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    //this sends the vertex data to the GPU:
    glBufferData( GL_ARRAY_BUFFER,                       //what buffer type
                 mVertices.size() * sizeof( Vertex ),   //how big buffer do we need
                 mVertices.data(),                      //the actual vertices
                 GL_STATIC_DRAW                         //should the buffer be updated on the GPU
                 );

    // 1st attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(
               0,                           // attribute. No particular reason for 0, but must match layout(location = 0) in the vertex shader.
               3,                           // size / number of elements of data type
               GL_FLOAT,                    // data type
               GL_FALSE,                    // normalize data
               sizeof(Vertex),         // stride
               reinterpret_cast<GLvoid*>(0  ));               // array buffer offset
    glEnableVertexAttribArray(0);


    // 2nd attribute buffer : colors
    // Same parameter list as above but attribute and offset is adjusted accoringly
    glVertexAttribPointer(
               1,
               3,
               GL_FLOAT,
               GL_FALSE,
               sizeof( Vertex ),
               reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Tetrahedron::draw(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    //just to make the triangle rotate - tweak this: degree, x,   y,   z -axis
    if(mRotate)
        mMatrix.rotate(2.0f, 0.0f, 1.0f, 0.0f);
}
