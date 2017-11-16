#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <vector>
#include "CrosswalkLight.h"
using namespace std;

class LightController {
public:
    LightController();
    LightController(vector<CrosswalkLight>&);
    void setCrosswalkLights(bool);

private:
    vector<CrosswalkLight> *crossLights;
};

#endif // LIGHTCONTROLLER_H
