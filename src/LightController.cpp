#include "LightController.h"
#include <vector>
#include "CrosswalkLight.h"
using namespace std;

LightController::LightController() {}

LightController::LightController(vector<CrosswalkLight> &cwl) {
    this->crossLights = &cwl;
}

void LightController::setCrosswalkLights(bool b) {
    for (CrosswalkLight& cwl : *crossLights) {
        cwl.setStatus(b);
	}
}
