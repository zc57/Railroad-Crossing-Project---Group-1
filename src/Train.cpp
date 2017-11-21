#include <iostream>
using std::cout;
using std::endl;
#include "Train.h"

Train::Train(int enterAfterSeconds, int l, TrainDetector &detIn, TrainDetector &detOut) {
    name = "Train";
    isActive = true;
    inIntersection = false;
    length = l;
    enterAfter = enterAfterSeconds;
    detectorIn = &detIn;
    detectorOut = &detOut;
}

void Train::update(int s) {
    if (!isActive) return;
    if (s == enterAfter) {
        detectorIn->detect();
    } else if (s == enterAfter + detectorIn->distance) {
        cout << "* Train entered Intersection" << endl;
        inIntersection = true;
        hitIntersectionAt = s;
    } else if (s == hitIntersectionAt + length) {
        detectorOut->detect();
        detectorIn->resetStatus();
        inIntersection = false;
        remove();
    }
}

void Train::remove() {
        isActive = false;
    }
