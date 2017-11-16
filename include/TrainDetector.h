#ifndef TRAINDETECTOR_H
#define TRAINDETECTOR_H
#include <vector>
#include "TrainBar.h"
#include "LightController.h"
using namespace std;

class TrainDetector
{
public:
    int distance;


    TrainDetector(bool, int, vector<TrainBar>&, LightController);
	bool isIncoming();
	void detect();
	void resetStatus();
	bool getStatus();
	void setRed();
	int getLightstatus();

private:
    vector<TrainBar> *trainBars;
    LightController lightController;
	bool incoming;
	bool status; //Move to a Controller object
	int light;

};

#endif // TRAINDETECTOR_H
