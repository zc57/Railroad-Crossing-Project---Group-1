#include <iostream>
#include <vector>
using namespace std;
#include "TrainDetector.h"
#include "TrainBar.h"

TrainDetector::TrainDetector(bool inc, vector<TrainBar> &trainBarsVector) {
    this->incoming = inc;
    this->trainBars = &trainBarsVector;
    this->status = 0;
    this->light = 0;
    this->distance = 2;
}

bool TrainDetector::isIncoming() {
    return incoming;
}

void TrainDetector::detect() {
    status = incoming;
    for (TrainBar& tb : *trainBars) {
        if (incoming) tb.lowerBar();
        else tb.raiseBar();
	}
}

void TrainDetector::resetStatus() {
    status = 0;
}

bool TrainDetector::getStatus() { // Controller Object
    return status;
}

void TrainDetector::setRed() {
    //incoming = true;
    if (incoming = true) {
        light = 0;
        cout << "TRAIN DETECTED!! Set all lights to red, including crosswalks" << endl;
        cout << "Lights should be set to: " << light << endl;
    }
    else {
        light = 1;
    }
}

int TrainDetector::getLightstatus() {
    return status;
}
