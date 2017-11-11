#include <iostream>
#include <vector>
using namespace std;
#include "PressurePad.h"
#include "TrainDetector.h"
#include "TrainCrossingLights.h"
#include "TrainBar.h"

class Actor {
public:
    string name;
    bool inIntersection;
    bool isActive;

    void update(int) {};
    void remove() {};
};

class Train : Actor {
public:
    int length;
    int enterAfter;
    bool isActive;
    TrainDetector *detectorIn, *detectorOut;

    Train() {};
    Train(int enterAfterSeconds, int l, TrainDetector &detIn, TrainDetector &detOut) {
        isActive = true;
        inIntersection = false;
        length = l;
        enterAfter = enterAfterSeconds;
        detectorIn = &detIn;
        detectorOut = &detOut;
    }
    void update(int s) {
        if (s == enterAfter) {
            detectorIn->detect();
        } else if (s == enterAfter + detectorIn->distance) {
            inIntersection = true;
        } else if (s == enterAfter + length + 1) {
            detectorOut->detect();
            detectorIn->resetStatus();
            inIntersection = false;
            remove();
        }
    }

    void remove() {
        isActive = false;
    }
};

int main () {
    int trainEnterAfter = 2;
    int trainLength = 3;

    vector<TrainBar> trainBars(0);
    TrainBar tb1(1), tb2(2), tb3(3), tb4(4), tb5(5), tb6(6);
	trainBars.push_back(tb1);
	trainBars.push_back(tb2);
	trainBars.push_back(tb3);
	trainBars.push_back(tb4);
	trainBars.push_back(tb5);
	trainBars.push_back(tb6);

	TrainDetector trainIn(true, trainBars);
	TrainDetector trainOut(false, trainBars);

	Train train = Train(trainEnterAfter, trainLength, trainIn, trainOut);

	int s = 0; //Seconds
    while (train.isActive) {
    cout << " STEP " << s << endl;
    train.update(s);
    cout << "Train Detector (In) : " << trainIn.getLightstatus() << endl;
    cout << "Train Detector (Out): " << trainOut.getLightstatus() << endl;
    for (TrainBar tb : trainBars) {
        cout << "Train Bar " << tb.getID() << ": " << (tb.getStatus() ? "Lowered" : "Raised") << endl;
	}

    s += 1;
    cout << "Press (Enter) to proceed)";
    cin.get();
    }
	return 0;
}
