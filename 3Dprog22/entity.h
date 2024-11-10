#ifndef ENTITY_H
#define ENTITY_H

// A basic entity with an integer identification - int Id;
struct Entity
{
    int Id;

    Entity(int x)
    {
        Id = x;
    }
};

#endif // ENTITY_H
