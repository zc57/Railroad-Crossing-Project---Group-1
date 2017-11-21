#include "TrafficLight.h"

TrafficLight::TrafficLight(string s)
{
    id = s;
    light = 0;
}

void TrafficLight::setLight(int l) {
    light = l;
}

int TrafficLight::getStatus() {
    return light;
}

string TrafficLight::getStatusString() {
    switch (light) {
    case 0: return "Red";
    case 1: return "Yellow";
    case 2: return "Green";
    }
}

string TrafficLight::getID() {
    return id;
}
