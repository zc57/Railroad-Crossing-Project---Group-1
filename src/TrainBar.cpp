#include "TrainBar.h"

TrainBar::TrainBar() {
    this->id = 0;
    this->lowered = false;
}

TrainBar::TrainBar(int id) {
    this->id = id;
    this->lowered = false;
}

void TrainBar::lowerBar() {
    lowered = true;
}

void TrainBar::raiseBar() {
    lowered = false;
}

bool TrainBar::getStatus() {
    return lowered;
}

int TrainBar::getID() {
    return id;
}
