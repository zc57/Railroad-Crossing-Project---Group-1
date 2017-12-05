#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "Actor.h"
#include "CrosswalkLight.h"

class Pedestrian : public Actor {
public:
    CrosswalkLight *destinationLight;
    int lengthToClear;

    Pedestrian();
    Pedestrian(int, CrosswalkLight*);
    void update(int);
    void remove();

private:
    int hitIntersectionAt;
};

#endif // PEDESTRIAN_H
