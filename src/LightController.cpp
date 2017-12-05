#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
#include "LightController.h"
#include "CrosswalkLight.h"

LightController::LightController() {}

LightController::LightController(vector<CrosswalkLight> &cwl, vector<TrainCrossingLights> &tcl, vector<TrafficLight> &tls, int secBetweenLights) {
    this->crossLights = &cwl;
    this->trainLights = &tcl;
    this->trafficLights = &tls;
    this->currentTrafficLight = 0;
    this->sinceLastTrafficChange = 0;
    this->secondsBetweenLights = secBetweenLights;
    changeTrafficLight();
}

void LightController::update(int s) {
    if (sinceLastTrafficChange >= secondsBetweenLights) {
        changeTrafficLight();
        sinceLastTrafficChange = 0;
    }
    sinceLastTrafficChange++;
}

void LightController::changeTrafficLight() {
    bool trainInIntersection = trainLights->at(0).getStatus();
    if (currentTrafficLight >= 0)
        trafficLights->at(currentTrafficLight).setLight(0);
    if (currentTrafficLight < 0)
        setCrosswalkLights(false);
    if (trainInIntersection)
        return;
    currentTrafficLight += 1;

    if (currentTrafficLight >= trafficLights->size()) {
        currentTrafficLight = -1;
    }
    if (currentTrafficLight >= 0) {
        trafficLights->at(currentTrafficLight).setLight(2);
    } else {
        setCrosswalkLights(true);
    }
}

void LightController::trainIncoming() {
    setTrafficLights(false);
    setCrosswalkLights(false);
    toggleTrainLights();
}

void LightController::trainOutgoing() {
    //setCrosswalkLights(true);
    toggleTrainLights();
}

void LightController::setTrafficLights(bool b) {
    for (TrafficLight& tl : *trafficLights) {
        tl.setLight(0);
    }
}

void LightController::setCrosswalkLights(bool b) {
    for (CrosswalkLight& cwl : *crossLights) {
        cwl.setStatus(b);
	}
}

void LightController::toggleTrainLights() {
    for (TrainCrossingLights& tcl : *trainLights) {
        tcl.setStatus(!tcl.getStatus());
    }
}
