#ifndef GRAPH_H
#define GRAPH_H

#include "visualobject.h"

class Graph : public VisualObject
{
public:
    Graph();
    Graph(std::string filnavn, bool nyGraf);
    ~Graph();

    void writeFile(std::string filnavn);
    void readFile(std::string filnavn);

    void init() override;
    void draw(GLint matrixUniform) override;
};

#endif // GRAPH_H
