#include <iostream>
using std::cout;
using std::endl;
#include "Car.h"

Car::Car(int len, TrafficLight *destLight) {
    name = "Car";
    isActive = true;
    inIntersection = false;
    hitIntersectionAt = 0;
    destinationLight = destLight;
    lengthToClear = len;
}

void Car::update(int s) {
    if (!isActive) return;
    if (!inIntersection && destinationLight->getStatus() > 0) {
        cout << "* Car entered intersection" << endl;
        inIntersection = true;
        hitIntersectionAt = s;
    } else if (inIntersection && s == hitIntersectionAt + lengthToClear) {
        cout << "* Car exited intersection" << endl;
        inIntersection = false;
        remove();
    }
}

void Car::remove() {
    isActive = false;
}
