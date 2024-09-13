#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(std::string filnavn, bool nyGraf)
{
    if (nyGraf)
    {
        float a = -1.0f, b = 1.0f, n = 11.0f;
        float h = (b - a) / n;

        float z = 0.0f;

        for (auto x = a; x <= b; x += h)
            {
                float y = pow(x, 2) - 1;
                mVertices.push_back(Vertex{x, y, z, (x - a) / (b - a), (y - a) / (b - a), z});
            }

        writeFile(filnavn);
    }
    else
        readFile(filnavn);
}

Graph::~Graph()
{

}

void Graph::writeFile(std::string filnavn)
{
    std::ofstream ut;
    ut.open(filnavn.c_str());

    if (ut.is_open())
    {
        auto n = mVertices.size();

        Vertex vertex;
        ut << n << std::endl;
        for (auto it=mVertices.begin(); it != mVertices.end(); it++)
        {
            ut << *it << std::endl;
        }

        ut.close();
    }
}

void Graph::readFile(std::string filnavn)
{
    std::ifstream inn;
    inn.open(filnavn.c_str());

    if (inn.is_open())
    {
        int n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        for (int i=0; i<n; i++)
        {
             inn >> vertex;
             mVertices.push_back(vertex);
        }
        inn.close();
    }
}

void Graph::init()
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

void Graph::draw(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
}
