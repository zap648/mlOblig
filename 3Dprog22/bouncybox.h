#ifndef BOUNCYBOX_H
#define BOUNCYBOX_H

#include "plane.h"

class BouncyBox : public Plane
{
private:
    std::vector<Plane*> p;
public:
    BouncyBox();
    BouncyBox(float w, float h, float l, bool roof = true);
    ~BouncyBox();
};

#endif // BOUNCYBOX_H
