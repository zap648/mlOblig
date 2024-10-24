#ifndef CONTROLLER_H
#define CONTROLLER_H


struct Controller
{
    bool moveUp{false};
    bool moveDown{false};
    bool moveLeft{false};
    bool moveRight{false};
    bool moveFor{false};
    bool moveBack{false};
    bool attack{false};
};

#endif // CONTROLLER_H
