#include "TrainCrossingLights.h"

TrainCrossingLights::TrainCrossingLights() {
    status = false;
}

bool TrainCrossingLights::getStatus() {
    return status;
}

void TrainCrossingLights::setStatus(bool b) {
    status = b;
}
