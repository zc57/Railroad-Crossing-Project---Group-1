#ifndef TRAINDETECTOR_H
#define TRAINDETECTOR_H
#include <vector>
#include "TrainBar.h"

class TrainDetector
{
public:
    int distance;
    vector<TrainBar> *trainBars;

    TrainDetector(bool, int, vector<TrainBar>&);
	bool isIncoming();
	void detect();
	void resetStatus();
	bool getStatus();
	void setRed();
	int getLightstatus();

private:
	bool incoming;
	bool status; //Move to a Controller object
	int light;

};

#endif // TRAINDETECTOR_H
