#include "Pedestrian.h"
#include <iostream>
using std::cout;
using std::endl;

Pedestrian::Pedestrian(int len, CrosswalkLight *destLight)
    : lengthToClear(len), destinationLight(destLight), hitIntersectionAt(1000) {
    name = "Pedestrian";
    isActive = true;
    inIntersection = false;
    }

void Pedestrian::update(int s) {
    if (!isActive) return;
    if (!inIntersection && destinationLight->getStatus()) {
        cout << "* Pedestrian entered intersection" << endl;
        inIntersection = true;
        this->hitIntersectionAt = s;
    } else if (s == hitIntersectionAt + lengthToClear) {
        cout << "* Pedestrian exited intersection" << endl;
        inIntersection = false;
        remove();
    }
}

void Pedestrian::remove() {
    isActive = false;
}
