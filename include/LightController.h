#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <vector>
using std::vector;
#include "CrosswalkLight.h"
#include "TrainCrossingLights.h"
#include "TrafficLight.h"

class LightController {
public:
    LightController();
    LightController(vector<CrosswalkLight>&, vector<TrainCrossingLights>&, vector<TrafficLight>&, int);
    void update(int);
    void setTrafficLights(bool);
    void setCrosswalkLights(bool);
    void toggleTrainLights();
    void trainIncoming();
    void trainOutgoing();
    void changeTrafficLight();

private:
    vector<CrosswalkLight> *crossLights;
    vector<TrainCrossingLights> *trainLights;
    vector<TrafficLight> *trafficLights;
    int currentTrafficLight;
    int sinceLastTrafficChange;
    int secondsBetweenLights;
};

#endif // LIGHTCONTROLLER_H
