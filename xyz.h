#ifndef XYZ_H
#define XYZ_H

#include <vector>
#include "visualobject.h"

class XYZ : public VisualObject
{
private:

public:
   XYZ();
   ~XYZ() override;

   bool mRotate{true};

   void init() override;
   void draw(GLint matrixUniform) override;
};
#endif // XYZ_H
