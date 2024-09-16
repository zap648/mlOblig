#include "interactiveobject.h"

InteractiveObject::InteractiveObject() : mx{0.0f}, my{0.0f}, mz{0.0f}
{

}

InteractiveObject::InteractiveObject(std::string fileName, bool newObject) : mx{0.0f}, my{0.0f}, mz{0.0f}
{
//    if (newObject)
//    {
//        // All Required Vertices
//        //     v   x     y     z     r     g     b
//        Vertex v0{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
//        Vertex v1{ 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f};
//        Vertex v2{-0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f};
//        Vertex v3{-0.5f, 0.0f,-0.5f, 1.0f, 0.0f, 0.0f};
//        Vertex v4{ 0.5f, 0.0f,-0.5f, 0.0f, 0.0f, 0.0f};

//        // Pyramid insert Vertives
//        mVertices.insert( mVertices.end(),
//                          {
//                              v0, v1, v2,   // Pyramid tri_1
//                              v0, v2, v3,   // Pyramid tri_2
//                              v0, v3, v4,   // Pyramid tri_3
//                              v0, v4, v1,   // Pyramid tri_4
//                              v3, v2, v1,   // Pyramid quad_1/2
//                              v3, v1, v4    // Pyramid quad_2/2
//                          });
//        writeFile(fileName);
//    }
//    else
//        readFile(fileName);

//    findNormal();
//    findUV();

//    mr = 1.0f;
}

InteractiveObject::~InteractiveObject()
{

}

void InteractiveObject::writeFile(std::string filnavn)
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

void InteractiveObject::readFile(std::string filnavn)
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

void InteractiveObject::findNormal()
{
    for(int i = 0; i <= mVertices.size() - 2; i += 3)
    {
        // Vertices MUST be drawn clockwise from an outside perspective to get the correct normal
        QVector3D normal = VisualObject::getVectorNormal(mVertices[i], mVertices[i + 2], mVertices[i + 1]);

        mVertices[i].m_normal[0] = normal.x();
        mVertices[i].m_normal[1] = normal.y();
        mVertices[i].m_normal[2] = normal.z();

        mVertices[i + 1].m_normal[0] = normal.x();
        mVertices[i + 1].m_normal[1] = normal.y();
        mVertices[i + 1].m_normal[2] = normal.z();

        mVertices[i + 2].m_normal[0] = normal.x();
        mVertices[i + 2].m_normal[1] = normal.y();
        mVertices[i + 2].m_normal[2] = normal.z();
    }
}

void InteractiveObject::findUV()
{
    int j = 0;
    for (int i = 0; i <= mVertices.size() - 2; i += 3)
    {
        if (j < 4)
        {
            mVertices[i].m_st[0] = 0.5f;
            mVertices[i].m_st[1] = 1.0f;

            mVertices[i + 1].m_st[0] = 1.0f;
            mVertices[i + 1].m_st[1] = 0.0f;

            mVertices[i + 2].m_st[0] = 0.0f;
            mVertices[i + 2].m_st[1] = 0.0f;
        }
        else
        {
            mVertices[i].m_st[0] = 0.0f;
            mVertices[i].m_st[1] = 0.0f;

            mVertices[i + 1].m_st[0] = 0.0f;
            mVertices[i + 1].m_st[1] = 1.0f;

            mVertices[i + 2].m_st[0] = 1.0f;
            mVertices[i + 2].m_st[1] = 1.0f;
        }
        j++;
    }
}

void InteractiveObject::init()
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

void InteractiveObject::draw(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    glBindVertexArray(mVAO);
    glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void InteractiveObject::move(float dx, float dy, float dz)
{
    mx += dx;
    my += dy;
    mz += dz;
    mr = 0.1f;

//    qDebug() << "move";
    mMatrix.translate(dx, dy, dz);
}

QVector3D InteractiveObject::getPosition()
{
    return {mx, my, mz};
}

float InteractiveObject::getRadius()
{
    return mr;
}
