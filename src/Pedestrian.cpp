#include "Pedestrian.h"
#include <iostream>
using std::cout;
using std::endl;

Pedestrian::Pedestrian(int len, CrosswalkLight &destLight) {
    name = "Pedestrian";
    isActive = true;
    inIntersection = false;
    lengthToClear = len;
    destinationLight = &destLight;
    hitIntersectionAt = 0;
}

void Pedestrian::update(int s) {
    if (!isActive) return;
    if (!inIntersection && destinationLight.getStatus()) {
        cout << "* Pedestrian entered intersection" << endl;
        inIntersection = true;
        hitIntersectionAt = s;
    } else if (s == hitIntersectionAt + lengthToClear) {
        cout << "* Pedestrian exited intersection" << endl;
        inIntersection = false;
        remove();
    }
}

void Pedestrian::remove() {
    isActive = false;
}
