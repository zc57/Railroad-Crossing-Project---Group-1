#ifndef CAR_H
#define CAR_H

#include "Actor.h"
#include "TrafficLight.h"

class Car : public Actor {
public:
    TrafficLight *destinationLight;

    Car();
    Car(int, TrafficLight *);

    void update(int);
    void remove();

private:
    int hitIntersectionAt;
    int lengthToClear;
};

#endif // CAR_H
