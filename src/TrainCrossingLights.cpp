#include "TrainCrossingLights.h"
#include <iostream>
using namespace std;


void TrainCrossingLights::trainWeightDetected(){
    trainWeight = true;
    cout << "There has been a train detected in the area and a signal will be sent to the lights" <<endl;
}

void TrainCrossingLights::notrainWeightDetected() {
    trainWeight = false;
    cout << "No train" << endl;
}

void TrainCrossingLights::flash(){
   if (trainWeight >= 20) {
        light = 0;
        cout<< "The lights would start to flash when train approaches" <<endl;
    } else {
        cout<< "The lights wouldn't flash" <<endl;
    }
}

