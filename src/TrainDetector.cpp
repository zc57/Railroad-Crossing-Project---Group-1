#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
#include "TrainDetector.h"
#include "TrainBar.h"
#include "LightController.h"

TrainDetector::TrainDetector(bool inc, int dist, vector<TrainBar> &trainBarsVector, LightController lc) {
    this->incoming = inc;
    this->trainBars = &trainBarsVector;
    this->lightController = lc;
    this->status = 0;
    this->light = 0;
    this->distance = dist;
}

bool TrainDetector::isIncoming() {
    return incoming;
}

void TrainDetector::detect() {
    cout << "* Train Detector (" << (incoming ? "Incoming" : "Outgoing") << ") triggered.\n";
    status = incoming;
    if (incoming) {
        for (TrainBar& tb : *trainBars) {
            tb.lowerBar();
        }
        lightController.setCrosswalkLights(false);
        lightController.toggleTrainLights();
	} else {
        for (TrainBar& tb : *trainBars) {
            tb.raiseBar();
        }
        lightController.setCrosswalkLights(true);
        lightController.toggleTrainLights();
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
    if (incoming) {
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
