#include <vector>
using std::vector;
#include "LightController.h"
#include "CrosswalkLight.h"

LightController::LightController() {}

LightController::LightController(vector<CrosswalkLight> &cwl, vector<TrainCrossingLights> &tcl) {
    this->crossLights = &cwl;
    this->trainLights = &tcl;
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
