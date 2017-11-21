#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <vector>
using std::vector;
#include "CrosswalkLight.h"
#include "TrainCrossingLights.h"

class LightController {
public:
    LightController();
    LightController(vector<CrosswalkLight>&, vector<TrainCrossingLights>&);
    void setCrosswalkLights(bool);
    void toggleTrainLights();

private:
    vector<CrosswalkLight> *crossLights;
    vector<TrainCrossingLights> *trainLights;
};

#endif // LIGHTCONTROLLER_H
