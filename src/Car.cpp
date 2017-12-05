#include <iostream>
using std::cout;
using std::endl;
#include "Car.h"

Car::Car(int len, TrafficLight *destLight)
    : lengthToClear(len), destinationLight(destLight), hitIntersectionAt(1000) {
    name = "Car";
    isActive = true;
    inIntersection = false;
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
